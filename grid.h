#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory> //för unique ptr
#include <random> // för slump
#include <algorithm> // för slump
#include <typeinfo> // för dynamic cast
#include "Cell.h" //cell bas-klassen
#include "Mine.h" //mine subclass
#include "NumCell.h" //numcell subclass

class Grid
{
private:
    bool running;
    int width;
    int height;
    float cellSize;
    int mineCount;

    std::vector<std::vector<std::unique_ptr<Cell>>> cells;

public:
    Grid(bool running, int width, int height, float cellSize, int mineCount);

    void initCells();
    void placeMines();
    void computeAdjacentCounts();

    bool isRunning() const { return running; }
    void reset();

    void handleClick(int mouseX, int mouseY, bool rightClick);
    void draw(sf::RenderWindow& window);
};

#endif
