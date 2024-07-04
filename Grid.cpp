#include "Grid.h"
#include <iostream>

#define LOG(text) std::cout << text <<std::endl;

Grid::Grid(int _size, sf::RenderWindow* _window)
{
    size = _size;
    window = _window;

}

void Grid::createGrid()
{
        

    // Get size of window and caluclate size of 1 grid cell
        sf::Vector2u windowSize = window->getSize();

        float cellSize = (float)windowSize.x / (float)size;
        

        float xPos = 0.f;
        float yPos = 0.f;

        // Create grid cells (nodes) and add them to a list.

        for (float y = 0; y < windowSize.y; y+= cellSize)
        {
            xPos =0;

            for (float x = 0; x < windowSize.x; x+=cellSize)
            {
                Node node(xPos,yPos,cellSize,window);

                nodes.push_back(node);


                xPos += cellSize;

            }

            yPos += cellSize;
        }

        drawGrid();

}

void Grid::drawGrid()
{

    // Draw each node
    window->clear(sf::Color::White);

    for(Node node: nodes)
    {
        node.draw();
    }


    window->display();
}

Node* Grid::updateGrid(sf::Vector2i mousePos, int keyMode )
{
    Node* nodeToReturn = nullptr;
    // Check if mouse clicks a node
    for (Node &node : nodes)
    {
        if(mousePos.x > node.xPos && mousePos.x < node.xPos + node.size && mousePos.y > node.yPos && mousePos.y < node.yPos + node.size)
        {
            // Depending on keymodes the nodes should be different. Only 1 start and end node are allowed so they are reset every click
            if(keyMode == 0)
            {

                for(Node &node: nodes)
                {
                    if(node.isStartNode)
                    {
                        node.isStartNode = false;
                        node.fill =0;
                    }
                    
                }

                
                node.isStartNode = true;
                //aStar->startNode = &node;
                node.fill = 1;
                drawGrid();
                
            }
            else if(keyMode == 1)
            {

                for(Node &node: nodes)
                {
                    if(node.isEndNode)
                    {
                        node.isEndNode = false;
                        node.fill =0;
                    }
                }

                node.isEndNode = true;
               // aStar->endNode = &node;
                node.fill = 1;
                drawGrid();
            }
            // Obstacles do not need to be reset since they dont require to be limited. Only limit is that they cant be drawn on start or end nodes.
            else if(keyMode==2)
            {
                if(!node.isEndNode && !node.isStartNode && node.fill ==0)
                {
                    std::cout <<"Fill\n";
                    node.fill =1;
                    node.isWalkable = false;
                    drawGrid();
                }
            }
            nodeToReturn = &node;

        }
        
    }

    return nodeToReturn;
}
    



    

