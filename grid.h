#ifndef GRID_H
#define GRID_H

#include <vector>
#include <random>
#include <map>
#include "Cell.h"
#include <SFML/Graphics.hpp>

class Grid
{
private:
    bool running;
    int width;
    int height;
    float cellSize;
    int mineCount;
    std::vector<std::vector<Cell>> cells;

public:
    // Constructor
    Grid(bool running, int width, int height, float cellSize, int mineCount);

    // Funntions to initialize grid
    void initCells();
    void placeMines();
    void computeAdjacentCounts();

    //setters and getters
    void setRunning(bool r) { running = r; }
    bool isRunning() const { return running; }

    // Getters and setters for cells
    Cell &getCell(int x, int y);
    void revealCell(int x, int y);
    void flagCell(int x, int y);

    // Settters and Getters for grid dimensions
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    void setWidth(int w) { width = w; }
    void setHeight(int h) { height = h; }

    void draw(sf::RenderWindow &window);
    void reset();

    //User input handling
    void handleClick(int mouseX, int mouseY, bool rightClick);

};

#endif
