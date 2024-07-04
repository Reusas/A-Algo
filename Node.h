#include "SFML/Graphics.hpp"

class Node
{

public:
    Node(float _xPos, float _yPos, int _size, sf::RenderWindow* _window);
    void draw();

    float xPos;
    float yPos;
    float size;

    Node* parent = nullptr;
    float g =0;
    float h =0;
    float f =0;
    bool fill = false;
    bool isWalkable = true;
    bool isStartNode = false;
    bool isEndNode = false;
    bool isChild = false;
    bool isPath = false;

private:
    sf::RenderWindow* window;
    sf::Color outlineColor = sf::Color(69,69,69,255);
    sf::Color color = sf::Color::Black;
    sf::Color startFillColor = sf::Color::Green;
    sf::Color endFillColor = sf::Color::Red;
    sf::Color childFillColor =sf::Color(255,255,0,255);
    sf::Color pathFillColor = sf::Color(0,0,255,255);
};