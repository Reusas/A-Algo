#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"


#ifndef ASTAR_H
#define ASTAR_H

class Node;
class Grid;

class AStar
{
    public:
    AStar();
    void Run();
    void Search(Grid* _grid);
    void constructPath(Grid* _grid);
    int calculateHeuristic(Node* startNode, Node* endNode);
    int KEY_MODE =0;
    Node* startNode;
    Node* endNode;

   
};

#endif

