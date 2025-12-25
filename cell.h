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

    virtual void setColour() {};
    virtual void setRevealed(bool r);

    bool getRevealed() const { return revealed; }
    bool getFlagged() const { return flagged; }
    void setFlagged(bool f);
    int getX() const { return x; }
    int getY() const { return y; }

    virtual void draw(sf::RenderWindow &window);
    virtual void print(std::ostream &os) const = 0;
};

inline std::ostream &operator<<(std::ostream &os, const Cell &cell)
{
    cell.print(os);
    return os;
}

#endif
