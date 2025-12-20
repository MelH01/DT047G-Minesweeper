#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>
#include <string>

class Cell
{
private:
    int x, y;
    bool mine = false;
    bool revealed = false;
    bool flagged = false;
    int adjacentMines = 0;

    sf::RectangleShape shape;
    sf::Text text;
    static sf::Font font;

public:
    // Constructor
    Cell(int x, int y, float size);

    // Getters
    int getX() const { return x; }
    int getY() const { return y; }
    bool isMine() const { return mine; }
    bool isRevealed() const { return revealed; }
    bool isFlagged() const { return flagged; }
    int &getAdjacentMines() { return adjacentMines; }   
    int getAdjacentMines() const { return adjacentMines; } 
    sf::Text getText() const { return text; }

    sf::RectangleShape &getShape() { return shape; }

    // Setters
    void setMine(bool m) { mine = m; }
    void setRevealed(bool r);
    void setFlagged(bool f);
    void setAdjacentMines(int c) { adjacentMines = c; }
    void setColour();
    void setText(const std::string &str) { text.setString(str); }
};

#endif
