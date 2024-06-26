#include <iostream>
#include "SFML/Window.hpp"
#include "Grid.h"
int main()
{
    // Used for detecting which mode of drawing user is in (start node - 0 end node 1 and obstacles -2)
    int KEY_MODE = 0;

    
    sf::RenderWindow window(sf::VideoMode(1000,1000), "Window");
    
    Grid grid(50);
    grid.createGrid(&window);

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
            if(KEY_MODE!= 2 && event.type == sf::Event::MouseButtonPressed)
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    grid.updateGrid(mousePos, &window, KEY_MODE);
                }
            }
            // If its drawing obstacles then detect mouse hold to allow for easier drawing of obstacles
            else if(KEY_MODE == 2 &&  sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                std::cout <<"Test";
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    grid.updateGrid(mousePos, &window, KEY_MODE);
                }
            }
            // Change drawing modes here
            if(event.type == sf::Event::KeyReleased)
            {
                if(event.key.scancode == sf::Keyboard::Scan::Num1)
                {
                    KEY_MODE = 0;
                }
                else if(event.key.scancode == sf::Keyboard::Scan::Num2)
                {
                    KEY_MODE = 1;
                }
                else if(event.key.scancode == sf::Keyboard::Scan::Num3)
                {
                    KEY_MODE = 2;
                }

            }

        }

    }

    return 0;
}