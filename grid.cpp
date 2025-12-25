#include "Grid.h"

Grid::Grid(bool running, int width, int height, float cellSize, int mineCount) : running(running), width(width), height(height), cellSize(cellSize), mineCount(mineCount)
{
    reset();
}

void Grid::initCells()
{
    cells.clear();
    cells.resize(height);

    for (int y = 0; y < height; y++)
    {
        cells[y].resize(width);
        for (int x = 0; x < width; x++)
        {
            cells[y][x] = std::make_unique<NumCell>(x, y, cellSize);
        }

    }
}

//Byter ut numCells på random positioner till minor
void Grid::placeMines()
{
    std::vector<std::pair<int, int>> pos;

    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            pos.push_back(std::make_pair(x, y));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(pos.begin(), pos.end(), gen);

    for (int i = 0; i < mineCount; i++)
    {
        auto [x, y] = pos[i];
        cells[y][x] = std::make_unique<Mine>(x, y, cellSize);
    }
}

void Grid::computeAdjacentCounts()
{
    static const int dirs[8][2] =
    {
        {-1,-1}, {-1,0}, {-1,1},
        {0,-1},          {0,1},
        {1,-1},  {1,0},  {1,1}
    };

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (!cells[y][x]->isMine())
                continue;

            for (auto& d : dirs)
            {
                int nx = x + d[0];
                int ny = y + d[1];

                if (nx < 0 || ny < 0 || nx >= width || ny >= height)
                    continue;

                cells[ny][nx]->incrementAdjacent();
                cells[ny][nx]->setColour();
            }
        }
    }
}

void Grid::draw(sf::RenderWindow& window)
{
    for (auto& row : cells)
        for (auto& cell : row)
            cell->draw(window);
}


//resetta gridet
void Grid::reset()
{
    running = true;

    initCells();
    placeMines();
    computeAdjacentCounts();
}

void Grid::handleClick(int mouseX, int mouseY, bool rightClick)
{
    int cx = mouseX / cellSize;
    int cy = mouseY / cellSize;

    if (cx < 0 || cy < 0 || cx >= width || cy >= height)
        return;

    Cell* cell = cells[cy][cx].get();

    if (rightClick && !cell->isRevealed())
    {
        cell->setFlagged(!cell->isFlagged());
        return;
    }

    if (cell->isFlagged() || cell->isRevealed())
        return;

    cell->reveal();

    if (cell->isMine())
    {
        running = false;
        return;
    }

    if (cell->getAdjacentMines() == 0)
    {
        static const int dirs[8][2] =
        {
            {-1,-1}, {-1,0}, {-1,1},
            {0,-1},          {0,1},
            {1,-1},  {1,0},  {1,1}
        };

        for (auto& d : dirs)
        {
            int nx = cx + d[0];
            int ny = cy + d[1];

            if (nx < 0 || ny < 0 || nx >= width || ny >= height)
                continue;

            handleClick(nx * cellSize + 1, ny * cellSize + 1, false);
        }
    }
}
