#include <SFML/Graphics.hpp>
#include "Grid.h"

int main()
{
    const int width = 10;
    const int height = 10;
    const float cellSize = 32.f;
    const int mineCount = 15;

    //init window
    sf::RenderWindow window(sf::VideoMode(width * cellSize, height * cellSize), "Minesweeper Test");

    // Init grid same val as window
    Grid grid(true, width, height, cellSize, mineCount);

    // init font for menu
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
        return -1;

    sf::Text menu("Game Over!", font, 24);
    menu.setFillColor(sf::Color::Black);
    menu.setPosition(10.f, 10.f);

    while (window.isOpen())
    {
        while (window.isOpen() && grid.isRunning())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                        grid.handleClick(event.mouseButton.x, event.mouseButton.y, false);
                    else if (event.mouseButton.button == sf::Mouse::Right)
                        grid.handleClick(event.mouseButton.x, event.mouseButton.y, true);
                }
            }

            window.clear(sf::Color::Black);
            grid.draw(window);
            window.display();
        }

        while (window.isOpen() && !grid.isRunning())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
                {
                    // Reset the board
                    grid.reset();
                }
            }

            window.clear(sf::Color::White);
            window.draw(menu);
            window.display();
        }
    }

    return 0;
}
