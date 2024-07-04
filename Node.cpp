#include "Node.h"

Node::Node(float _xPos, float _yPos, int _size, sf::RenderWindow* _window)
{
    xPos = _xPos;
    yPos = _yPos;
    size = _size;
    window = _window;
}

void Node::draw()
{

    sf::RectangleShape square(sf::Vector2f(size,size));

    // If this node isint filled just draw its outline
    square.setOutlineColor(outlineColor);
    if(fill == 0)
    {

       // Do nothing only need the outline
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
        else if(isChild)
        {
            square.setFillColor(childFillColor);
        }
        else if(isPath)
        {
            square.setFillColor(pathFillColor);
        }
        else
        {
            square.setFillColor(color);
            isWalkable = false;
        }
    }

    square.setOutlineThickness(1.f);
    square.setPosition(sf::Vector2f(xPos,yPos));
    window->draw(square);


}

