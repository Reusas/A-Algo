#include "Maze.h"
#include "Grid.h"
#include <iostream>
#include <algorithm>


Maze::Maze(Grid* _grid)
{
    grid = _grid;
}

void Maze::GenerateMaze()
{


    if(!isGenerating)
    {
        isGenerating = true;
        grid->clear(1);

        // Starting node is 0 but can be random 
        Node* startingNode = &grid->nodes[0];
        // Update the grid to show the start node
        startingNode->fillNode(sf::Color::White);
        startingNode->isWalkable = true;
        int index = startingNode->index;

        // Compute its frontier cells
        std::vector<Node*> frontierCells = computeFrontierCells(index);


        for(Node* node : frontierCells)
        {
            node->fillNode(node->childFillColor);
            std::cout << node->_frontierStatus << std::endl;
            
        }

        while(frontierCells.size() != 0)
        {
            // Get a random frontier cell and get its frontier cells
            int randomIndex = rand() % frontierCells.size();

            
            Node* frontierCell = frontierCells[randomIndex];
            Node* passageCell = nullptr;
            frontierCell->fill =0;
            frontierCell->isWalkable = true;

            // Depending on which direction its from i will get the index of the node between the current node and it. So if left is index 1 and the frontier is index 3 and i know its on the right it would be 3 - 1 or index 2 for the wall that needs to be a passage.
            if(frontierCell->_frontierStatus == Node::LEFT)
            {
                passageCell = &grid->nodes[frontierCell->index + 1];

            }
            else if(frontierCell->_frontierStatus == Node::RIGHT)
            {
                passageCell = &grid->nodes[frontierCell->index - 1];
            }
            else if(frontierCell->_frontierStatus == Node::UP)
            {
                passageCell = &grid->nodes[frontierCell->index + grid->size];
            }
            else if(frontierCell->_frontierStatus == Node::DOWN)
            {      
                passageCell = &grid->nodes[frontierCell->index - grid->size];
            }

            passageCell->fillNode(sf::Color::White);
            passageCell->fill = 0;
            passageCell->isWalkable = true;
            
            // Get frontier cells of that cell and loop

            std::vector<Node*> frontierCells2 = computeFrontierCells(frontierCell->index);
            for(Node* node : frontierCells2)
            {
                node->fillNode(node->childFillColor);
                std::cout << node->_frontierStatus << std::endl;

                frontierCells.push_back(node);


            }
            auto it = std::find(frontierCells.begin(),frontierCells.end(),frontierCell);
            frontierCells.erase(it);

            
            grid->drawGrid();

            


        }





    }

    isGenerating = false;

}

// Function to get frontier cells and the direction that will be useful for clearing passages.
std::vector<Node*> Maze::computeFrontierCells(int index)
{
    std::vector<Node*> frontierCells;

        if((index +2) % grid->size != 0 && (index +1) % grid->size != 0)
        {
            Node* rightNode = &grid->nodes[index +2];
            if(!rightNode->isWalkable)
            {
                std::cout << "Right node created" << std::endl;
                frontierCells.push_back(rightNode);
                rightNode->_frontierStatus = Node::RIGHT;
            }

        }

        if(index  % grid->size != 0 && index  % grid->size != 1)
        {
             Node* leftNode = &grid->nodes[index -2];
             if(!leftNode->isWalkable)
             {
                std::cout << "Left node created" << std::endl;
                frontierCells.push_back(leftNode);
                leftNode->_frontierStatus = Node::LEFT;
             }

        }

        if(index - (grid->size * 2) >=0)
        {
           Node* upNode = &grid->nodes[index - grid->size * 2];
           if(!upNode->isWalkable)
           {
                std::cout << "Up node created:" << index << std::endl;
                frontierCells.push_back(upNode);
                upNode->_frontierStatus = Node::UP;
           }

        }

        if(index + grid->size < grid->size * grid->size)
        {
            Node* downNode =&grid->nodes[index +grid->size * 2];
            if(!downNode->isWalkable)
            {
                std::cout << "Down node created" << std::endl;
                frontierCells.push_back(downNode);
                downNode->_frontierStatus = Node::DOWN;
            }

        }
    

    return frontierCells;
}