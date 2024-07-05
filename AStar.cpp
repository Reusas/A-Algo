#include "AStar.h"
#include "Grid.h"
#include <iostream>
#include <algorithm>
#include <math.h>
#define LOG(text) std::cout << text <<std::endl;
AStar::AStar()
{

}

void AStar::Search(Grid* _grid)
{
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
        int index = currentNode->index;



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

            int tentG = currentNode->g +_grid->cellSize;
            auto openIt = std::find(openList.begin(),openList.end(),node);
            if(openIt == openList.end())
            {

                
                node->parent = currentNode;
                node->g = tentG;
                node->h = calculateHeuristic(node, endNode);
                node->f = node->g + node->h;
                node->fillNode(node->childFillColor);
                openList.push_back(node);
                _grid->drawGrid();



            }

            else
            {
                if(tentG < node->g)
                {
                    node->parent = currentNode;
                    node->g = tentG;
                    node->f = node->g + node->h;
                }
            }

                

        }



    }


}

int AStar::calculateHeuristic(Node* startNode, Node* endNode)
{
    int h = 0;

    int xDist = std::abs(startNode->xPos - endNode->xPos);
    int yDist = std::abs(startNode->yPos - endNode->yPos);

    h =xDist + yDist;
    return h;

}

void AStar::constructPath(Grid* _grid)
{
        Node* parentNode = endNode->parent;

        while(parentNode != nullptr)
        {
            if(parentNode!= startNode)
            {
                parentNode->fillNode(parentNode->pathFillColor);
                _grid->drawGrid();
            }

            parentNode = parentNode->parent;
        }

    
}
