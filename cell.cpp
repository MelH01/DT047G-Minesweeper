#include "Cell.h"
#include <iostream>

sf::Font Cell::font;

Cell::Cell(int x, int y, float size) : x(x), y(y)
{
    // init shape of cell
    shape.setSize({size, size});
    shape.setPosition(x * size, y * size);
    shape.setFillColor(sf::Color::White);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(-1);

    // init text
    static bool loaded = false;
    if (!loaded)
    {
        if (!font.loadFromFile("arial.ttf"))
            std::cerr << "Failed to load font!" << std::endl;
        loaded = true;
    }
    text.setFont(font);
    text.setCharacterSize(size * 0.6);
    text.setPosition(x * size + size * 0.25f, y * size + size * 0.05f);
    text.setFillColor(sf::Color::Black); 
}

void Cell::setRevealed(bool r)
{
    revealed = r;
    if (revealed)
    {
        shape.setFillColor(sf::Color(200, 200, 200));
        if (mine)
            text.setString("X"); // mine
        else if (adjacentMines > 0)
            text.setString(std::to_string(adjacentMines)); // numbered
        else
            text.setString(""); // empty
    }
}

void Cell::setFlagged(bool f)
{
    flagged = f;
    // Optional: change color for flagged cells
    shape.setFillColor(flagged ? sf::Color::Red : sf::Color::White);
}

void Cell::setColour()
{
    if(isMine())
        return; // Mines retain their default color
    switch(adjacentMines)
    {
        case 1: text.setFillColor(sf::Color::Blue); break;
        case 2: text.setFillColor(sf::Color::Green); break;
        case 3: text.setFillColor(sf::Color::Red); break;
        case 4: text.setFillColor(sf::Color(128, 0, 128)); break; // Purple
        case 5: text.setFillColor(sf::Color(139, 69, 19)); break; // Brown
        case 6: text.setFillColor(sf::Color::Cyan); break;
        case 7: text.setFillColor(sf::Color::Black); break;
        case 8: text.setFillColor(sf::Color(128, 128, 128)); break; // Gray
        default: text.setFillColor(sf::Color::Transparent); break;
    }
}