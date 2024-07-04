#include "SFML/Graphics.hpp"
#include <vector>
#include "Node.h"

#ifndef GRID_H
#define GRID_H




class Grid
{
public:
    int size;
    Grid(int _size, sf::RenderWindow* _window);
    void createGrid();
    void drawGrid();
    Node* updateGrid(sf::Vector2i mousePos, int keyMode);
    std::vector<Node> nodes;
    

private:
    sf::RenderWindow* window;
    sf::Color cellColor = sf::Color::Black;
    sf::Color defaultCellColor = sf::Color::White;



};

#endif
