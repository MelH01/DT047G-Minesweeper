#include "NumCell.h"

NumCell::NumCell(int x, int y, float size) : Cell(x, y, size) {}

void NumCell::setAdjacentMines(int n)
{
    adjacentMines = n;
}

int NumCell::getAdjacentMines() const
{
    return adjacentMines;
}

void NumCell::setRevealed(bool r)
{
    revealed = r;
    if (r)
    {
        shape.setFillColor(sf::Color(200, 200, 200));

        if (adjacentMines > 0)
            text.setString(std::to_string(adjacentMines));
    }
}

void NumCell::setColour()
{
    switch (adjacentMines)
    {
    case 1:
        text.setFillColor(sf::Color::Blue);
        break;
    case 2:
        text.setFillColor(sf::Color::Green);
        break;
    case 3:
        text.setFillColor(sf::Color::Red);
        break;
    case 4:
        text.setFillColor(sf::Color(128, 0, 128));
        break; // Purple
    case 5:
        text.setFillColor(sf::Color(139, 69, 19));
        break; // Brown
    case 6:
        text.setFillColor(sf::Color::Cyan);
        break;
    case 7:
        text.setFillColor(sf::Color::Black);
        break;
    case 8:
        text.setFillColor(sf::Color(128, 128, 128));
        break; // Gray
    default:
        text.setFillColor(sf::Color::Transparent);
        break;
    }
}