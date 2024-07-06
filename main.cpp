#include <iostream>
#include "AStar.h"
#include "Grid.h"
#include "Maze.h"


const int GRID_SIZE =40;


int main()
{
    sf::RenderWindow window(sf::VideoMode(1000,1000), "Window");
    
    Grid grid(GRID_SIZE, &window);
    grid.createGrid();

    AStar aStar = AStar();

    Maze maze = Maze(&grid);

    while (window.isOpen())
    {

        sf::Event event;

        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        // If the user is in the first two drawing nodes (their drawing the start or end node) then only detect mouse clicks
            if(aStar.KEY_MODE!= 2 && event.type == sf::Event::MouseButtonPressed)
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if(aStar.KEY_MODE == 0)
                    {
                        Node* _startNode = grid.updateGrid(mousePos, aStar.KEY_MODE);
                        aStar.startNode = _startNode;
                    }
                    else if (aStar.KEY_MODE == 1)
                    {
                        Node* _endNode = grid.updateGrid(mousePos, aStar.KEY_MODE);
                        aStar.endNode = _endNode;
                    }

                    
                }
            }
            // If its drawing obstacles then detect mouse hold to allow for easier drawing of obstacles
            else if(aStar.KEY_MODE == 2 &&  sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {

                   
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                grid.updateGrid(mousePos, aStar.KEY_MODE);
                
            }

            else if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {

                   
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                grid.updateGrid(mousePos, 3);
                
            }
            // Change drawing modes here
            if(event.type == sf::Event::KeyReleased)
            {
                if(event.key.scancode == sf::Keyboard::Scan::Num1)
                {
                    aStar.KEY_MODE = 0;
                }
                else if(event.key.scancode == sf::Keyboard::Scan::Num2)
                {
                    aStar.KEY_MODE = 1;
                }
                else if(event.key.scancode == sf::Keyboard::Scan::Num3)
                {
                    aStar.KEY_MODE = 2;
                }
                else if(event.key.scancode == sf::Keyboard::Scan::Enter)
                {
                    aStar.Search(&grid);
                }
                else if (event.key.scancode == sf::Keyboard::Scan::Escape)
                {
                    grid.clear(0);
                }
                else if (event.key.scancode == sf::Keyboard::Scan::Space)
                {
                    maze.GenerateMaze();
                }

            }

        }

    }
    

}