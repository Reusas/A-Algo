#include "SFML/Graphics.hpp"
#include <vector>
#include "Node.h"

#ifndef GRID_H
#define GRID_H

class AStar;


class Grid
{
public:
    int size;
    Grid(int _size, AStar* _aStar);
    void createGrid(sf::RenderWindow* window);
    void drawGrid(sf::RenderWindow* window);
    void updateGrid(sf::Vector2i mousePos, sf::RenderWindow* window, int keyMode);
    std::vector<Node> nodes;
    

private:
    sf::Color cellColor = sf::Color::Black;
    AStar* aStar;


};

#endif
