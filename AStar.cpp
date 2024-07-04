#include "AStar.h"
#include "Grid.h"
#include <iostream>
#include <algorithm>
#define LOG(text) std::cout << text <<std::endl;
AStar::AStar()
{

}

void AStar::Run()
{
    
    sf::RenderWindow window(sf::VideoMode(1000,1000), "Window");
    
    Grid grid(50, &window);
    grid.createGrid();

    while (window.isOpen())
    {

        sf::Event event;

        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        // If the user is in the first two drawing nodes (their drawing the start or end node) then only detect mouse clicks
            if(KEY_MODE!= 2 && event.type == sf::Event::MouseButtonPressed)
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if(KEY_MODE == 0)
                    {
                        Node* _startNode = grid.updateGrid(mousePos, KEY_MODE);
                        startNode = _startNode;
                    }
                    else if (KEY_MODE == 1)
                    {
                        Node* _endNode = grid.updateGrid(mousePos, KEY_MODE);
                        endNode = _endNode;
                    }

                    
                }
            }
            // If its drawing obstacles then detect mouse hold to allow for easier drawing of obstacles
            else if(KEY_MODE == 2 &&  sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    grid.updateGrid(mousePos, KEY_MODE);
                }
            }
            // Change drawing modes here
            if(event.type == sf::Event::KeyReleased)
            {
                if(event.key.scancode == sf::Keyboard::Scan::Num1)
                {
                    KEY_MODE = 0;
                }
                else if(event.key.scancode == sf::Keyboard::Scan::Num2)
                {
                    KEY_MODE = 1;
                }
                else if(event.key.scancode == sf::Keyboard::Scan::Num3)
                {
                    KEY_MODE = 2;
                }
                else if(event.key.scancode == sf::Keyboard::Scan::Enter)
                {
                    Search(&grid);
                }

            }

        }

    }
    
}

void AStar::Search(Grid* _grid)
{
    LOG("Starting algo");
    std::vector<Node*> openList;
    std::vector<Node*> closedList;

    openList.push_back(startNode);

    while(!openList.empty())
    {

        // Node with the currently lowest F value
        Node* currentNode = openList[0];

        // Look for lowest F value
        for(Node* node : openList)
        {
            if(node->f < currentNode->f)
            {
                currentNode = node;
            }
        }
        // Remove it from the openList and add it to the closed list
        auto it = std::find(openList.begin(),openList.end(),currentNode);
        openList.erase(it);
        std::cout << "Open list size after erasure:" << openList.size() << std::endl;
        closedList.push_back(currentNode);
        
        if(currentNode == endNode)
        {
            constructPath(_grid);
            break;
        }
        // Generate children
        int index = 0;

        // Loop through nodes to get current nodes index in the list
        for(Node node : _grid->nodes)
        {
            if((&node)->xPos == currentNode->xPos && (&node)->yPos == currentNode->yPos)
            {
                LOG(index);
                
                break;
            }
            index = index + 1;
            
        }

        // Create children here
        std::vector<Node*> childNodes;

        if((index +1) % _grid->size != 0)
        {
            Node* rightNode = &_grid->nodes[index +1];
            childNodes.push_back(rightNode);
        }

        if(index % _grid->size != 0)
        {
             Node* leftNode = &_grid->nodes[index -1];
             childNodes.push_back(leftNode);
        }

        if(index - _grid->size >=0)
        {
           Node* upNode = &_grid->nodes[index - _grid->size];
           childNodes.push_back(upNode);
        }

        if(index + _grid->size < _grid->size * _grid->size)
        {
            Node* downNode =&_grid->nodes[index +_grid->size];
            childNodes.push_back(downNode);
        }





        for(Node* node : childNodes)
        {
            
            if(!node->isWalkable || std::find(closedList.begin(),closedList.end(), node) !=closedList.end())
            {
                continue;
            }

            auto openIt = std::find(openList.begin(),openList.end(),node);
            if(openIt == openList.end())
            {

                node->parent = currentNode;
                node->g = currentNode->g + 1;
                node->h = calculateHeuristic(node, endNode);
                node->f = node->g + node->h;
                node->isChild = true;
                node->fill = 1;
                openList.push_back(node);
                _grid->drawGrid();
            }

            else
            {
                if(node->g > currentNode->g)
                {
                    node->parent = currentNode;
                    node->g = currentNode->g + 1;
                    node->f = node->g + node->h;
                }
            }
                        

        }


    }
    LOG("Algo Finished.");



}

int AStar::calculateHeuristic(Node* startNode, Node* endNode)
{
    int h = 0;

    int xDist = std::abs(startNode->xPos - endNode->xPos);
    int yDist = std::abs(startNode->yPos - endNode->yPos);

    h = xDist + yDist;
    return h;

}

void AStar::constructPath(Grid* _grid)
{
        Node* parentNode = endNode->parent;

        while(parentNode != nullptr)
        {
            parentNode->fill = 1;
            parentNode->isChild = false;
            parentNode->isPath = true;
            parentNode->draw();
            _grid->drawGrid();
            parentNode = parentNode->parent;
        }

    
}
