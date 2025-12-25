#include "mine.h"

Mine::Mine(int x, int y, float size) : Cell(x, y, size){}

void Mine::reveal()
{
    revealed = true;
    shape.setFillColor(sf::Color(200, 200, 200));
    text.setString("X");
}
