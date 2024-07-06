#include "Node.h"

Node::Node(float _xPos, float _yPos,int _index, int _size, sf::RenderWindow* _window)
{
    xPos = _xPos;
    yPos = _yPos;
    index = _index;
    size = _size;
    window = _window;
}


void Node::reset()
{
     parent = nullptr;
     g =0;
     h =0;
     f =0;
     fill = false;
     isWalkable = true;
     isStartNode = false;
     isEndNode = false;
}
void Node::draw()
{

    sf::RectangleShape square(sf::Vector2f(size,size));

    // If this node isint filled just draw its outline
    square.setOutlineColor(outlineColor);

    
    if (fill == 1)
    {
        square.setFillColor(fillColor);
    }

    square.setOutlineThickness(1.f);
    square.setPosition(sf::Vector2f(xPos,yPos));
    window->draw(square);


}

void Node::fillNode(sf::Color _fillColor)
{
    if(_fillColor != sf::Color::White)
    {
        fill = true;
    }
    if(!isEndNode)
    {
        fillColor = _fillColor;
    }
}

