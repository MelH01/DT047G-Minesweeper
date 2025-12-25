#include "cell.h"
#include <iostream>

sf::Font Cell::font;

Cell::Cell(int x, int y, float size) : x(x), y(y)
{
    shape.setSize({ size, size });
    shape.setPosition(x * size, y * size);
    shape.setFillColor(sf::Color::White);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(-1);

    static bool loaded = false;
    if (!loaded)
    {
        if (!font.loadFromFile("arial.ttf"))
            std::cerr << "Font load failed\n";
        loaded = true;
    }

    text.setFont(font);
    text.setCharacterSize(size * 0.6f);
    text.setPosition(x * size + size * 0.25f, y * size + size * 0.05f);
    text.setFillColor(sf::Color::Black);
}

void Cell::setFlagged(bool f)
{
    flagged = f;
    shape.setFillColor(flagged ? sf::Color::Red : sf::Color::White);
}

void Cell::draw(sf::RenderWindow& window)
{
    window.draw(shape);
    window.draw(text);
}
