#include "mine.h"

Mine::Mine(int x, int y, float size)
    : Cell(x, y, size)
{
}

bool Mine::isMine() const
{
    return true;
}

void Mine::incrementAdjacent()
{
    // Mines do not track adjacency
}

int Mine::getAdjacentMines() const
{
    return -1; // meaningless for mines
}

void Mine::reveal()
{
    revealed = true;
    shape.setFillColor(sf::Color(200, 200, 200));
    text.setString("X");
}
