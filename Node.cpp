#include "Node.h"
#include <iostream>

Node::Node(float _xPos, float _yPos, int _size)
{
    xPos = _xPos;
    yPos = _yPos;
    size = _size;
}

void Node::draw(sf::RenderWindow* window)
{

    sf::RectangleShape square(sf::Vector2f(size,size));

    // If this node isint filled just draw its outline
    if(fill == 0)
    {

        square.setOutlineColor(color);
    }
    // If it is filled then depending on if its a start node or not change its color
    else if (fill == 1)
    {
        if(isStartNode)
        {
            square.setFillColor(startFillColor);
        }
        else if(isEndNode)
        {
            square.setFillColor(endFillColor);
        }
        else
        {
            square.setFillColor(color);
        }
    }

    square.setOutlineThickness(1.f);
    square.setPosition(sf::Vector2f(xPos,yPos));
    window->draw(square);


}

