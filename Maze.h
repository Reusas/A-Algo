#include <vector>

#ifndef MAZE_H
#define MAZE_H

class Node;
class Grid;

class Maze
{
public:
    Maze(Grid* _grid);
    void GenerateMaze();
    std::vector<Node*> computeFrontierCells(int index);

private:
    Grid* grid;
    bool isGenerating = false;
};

#endif