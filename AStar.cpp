#include "AStar.h"
#include "Grid.h"
#include <algorithm>
#include <queue>
AStar::AStar()
{

}

void AStar::Search(Grid* _grid)
{
    std::vector<Node*> openList;
    std::vector<Node*> closedList;


    struct fCheck
    {
        bool operator()(Node* a, Node* b)
        {
            return a->f > b->f;
        }
    };

    std::priority_queue<Node*,std::vector<Node*>,fCheck> openSet;
        
        openList.push_back(startNode);
        openSet.push(startNode);







   // openList.push_back(startNode);

    while(!openSet.empty())
    {

        // Node with the currently lowest F value
        Node* currentNode = openSet.top();


        // Remove it from the openList and add it to the closed list
        openSet.pop();
        closedList.push_back(currentNode);
        
        if(currentNode == endNode)
        {
            constructPath(_grid);
            break;
        }
        // Get index of node in the list to know where children are
        int index = currentNode->index;



        // Create children here
        // Using the index as an offset i can get the children
        std::vector<Node*> childNodes;

        // Checking if is in range.
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
                openSet.push(node);
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
                    openSet.push(node);
                }
            }

                

        }



    }


}
// Manhattan distance heuristic
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
