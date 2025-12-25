#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>
#include <string>

class Cell
{
protected:
    int x, y;
    bool revealed = false;
    bool flagged = false;

    sf::RectangleShape shape;
    sf::Text text;

    static sf::Font font;

public:
    Cell(int x, int y, float size);
    virtual ~Cell() = default;

    virtual void reveal() = 0;
    virtual void setColour() {}; 

    bool isRevealed() const { return revealed; }
    bool isFlagged() const { return flagged; }
    void setFlagged(bool f);
    int getX() const { return x; }
    int getY() const { return y; }

    virtual void draw(sf::RenderWindow& window);

};

#endif
