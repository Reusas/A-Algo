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
        std::vector<Node*> mazeList;
        std::vector<Node*> wallList;

        grid->clear(1);

        // Grab a random node to be the start
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
            int randomIndex = rand() % frontierCells.size();

            
            Node* frontierCell = frontierCells[randomIndex];
            Node* passageCell = nullptr;
            frontierCell->fill =0;
            frontierCell->isWalkable = true;

            if(frontierCell->_frontierStatus == Node::LEFT)
            {
                passageCell = &grid->nodes[frontierCell->index + 1];
                std::cout << "This node is left:" << passageCell;

            }
            else if(frontierCell->_frontierStatus == Node::RIGHT)
            {
                passageCell = &grid->nodes[frontierCell->index - 1];
                std::cout << "This node is right:" << passageCell;
            }
            else if(frontierCell->_frontierStatus == Node::UP)
            {
                passageCell = &grid->nodes[frontierCell->index + grid->size];
                std::cout << "This node is up:" << passageCell;
            }
            else if(frontierCell->_frontierStatus == Node::DOWN)
            {      
                passageCell = &grid->nodes[frontierCell->index - grid->size];
                std::cout << "This node is down:" << passageCell;
            }

            passageCell->fillNode(sf::Color::White);
            passageCell->fill = 0;
            passageCell->isWalkable = true;
            

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


std::vector<Node*> Maze::computeFrontierCells(int index)
{
    std::vector<Node*> frontierCells;

        if((index +2) % grid->size != 0 && (index +1) % grid->size != 0)
        {
            Node* rightNode = &grid->nodes[index +2];
            if(!rightNode->isWalkable)
            {
                frontierCells.push_back(rightNode);
                rightNode->_frontierStatus = Node::RIGHT;
            }

        }

        if(index % grid->size != 0)
        {
             Node* leftNode = &grid->nodes[index -2];
             if(!leftNode->isWalkable)
             {
                frontierCells.push_back(leftNode);
                leftNode->_frontierStatus = Node::LEFT;
             }

        }

        if(index - grid->size >=0)
        {
           Node* upNode = &grid->nodes[index - grid->size * 2];
           if(!upNode->isWalkable)
           {
                frontierCells.push_back(upNode);
                upNode->_frontierStatus = Node::UP;
           }

        }

        if(index + grid->size < grid->size * grid->size)
        {
            Node* downNode =&grid->nodes[index +grid->size * 2];
            if(!downNode->isWalkable)
            {
                frontierCells.push_back(downNode);
                downNode->_frontierStatus = Node::DOWN;
            }

        }

    return frontierCells;
}