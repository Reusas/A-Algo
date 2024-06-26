#include "SFML/Graphics.hpp"
#include <vector>
#include "Node.h"
class Grid
{
public:
    Grid(int _size);
    void createGrid(sf::RenderWindow* window);
    void drawGrid(sf::RenderWindow* window);
    void updateGrid(sf::Vector2i mousePos, sf::RenderWindow* window, int keyMode);
    std::vector<Node> nodes;


private:
    int size;
    sf::Color cellColor = sf::Color::Black;

};