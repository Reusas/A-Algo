#include "SFML/Graphics.hpp"

class Node
{

public:
    Node(float _xPos, float _yPos, int _size);
    void draw(sf::RenderWindow* window);

    float xPos;
    float yPos;
    float size;
    bool fill = false;
    bool isStartNode = false;
    bool isEndNode = false;

private:
    sf::Color color = sf::Color::Black;
    sf::Color startFillColor = sf::Color::Green;
    sf::Color endFillColor = sf::Color::Red;
};