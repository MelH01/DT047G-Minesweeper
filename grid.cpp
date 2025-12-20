#include "Grid.h"

Grid::Grid(bool running, int width, int height, float cellSize, int mindCount) : running(running), width(width), height(height), cellSize(cellSize), mineCount(mindCount)
{
    initCells();
    placeMines();
    computeAdjacentCounts();
    for (auto &row : cells)
        for (auto &c : row)
            c.setColour();
}

void Grid::initCells()
{
    cells.reserve(height);

    for (int y = 0; y < height; y++)
    {
        std::vector<Cell> row;
        row.reserve(width);

        for (int x = 0; x < width; x++)
        {
            row.emplace_back(x, y, cellSize);
        }

        cells.push_back(row);
    }
}

void Grid::placeMines()
{
    std::vector<std::pair<int, int>> cellsTmp;

    // Collect all cells
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            cellsTmp.push_back({x, y});
        }
    }

    // Shuffle coordinates
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(cellsTmp.begin(), cellsTmp.end(), gen);

    // Set mines
    for (int i = 0; i < mineCount; i++)
    {
        auto [x, y] = cellsTmp[i];
        cells[y][x].setMine(true);
    }
}

void Grid::computeAdjacentCounts()
{
    static const int dirs[8][2] =
        {
            {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (!cells[y][x].isMine())
                continue;

            // For each mine, increment its neighbors
            for (auto &d : dirs)
            {
                int nx = x + d[0];
                int ny = y + d[1];

                // boundary check
                if (nx < 0 || ny < 0 || nx >= width || ny >= height)
                    continue;

                cells[ny][nx].getAdjacentMines()++;
            }
        }
    }
}

Cell &Grid::getCell(int x, int y)
{
    return cells[y][x];
}

void Grid::revealCell(int x, int y)
{
    cells[y][x].setRevealed(true);
}

void Grid::flagCell(int x, int y)
{
    bool old = cells[y][x].isFlagged();
    cells[y][x].setFlagged(!old);
}

void Grid::draw(sf::RenderWindow &window)
{
    for (auto &row : cells)
        for (auto &c : row)
        {
            window.draw(c.getShape());
            window.draw(c.getText());
        }
}

void Grid::reset()
{
    for (auto &row : cells)
        for (auto &c : row)
        {
            c.setRevealed(false);
            c.setFlagged(false);
            c.setText("");
        }
}

void Grid::handleClick(int mouseX, int mouseY, bool rightClick)
{
    // get loc
    int cx = mouseX / cellSize;
    int cy = mouseY / cellSize;

    // check boundries
    if (cx < 0 || cy < 0 || cx >= width || cy >= height)
        return;

    // get cell 
    Cell &cell = cells[cy][cx];

    if (rightClick)
    {
        cell.setFlagged(!cell.isFlagged());
    }
    else
    {
        cell.setRevealed(true);

        if (cell.isMine())
        {
            reset();
            return;
        }

        // recursive flood fill (like paint)
        if (cell.getAdjacentMines() == 0 && !cell.isMine())
        {
            static const int dirs[8][2] =
                {
                    {-1, -1}, {-1, 0}, {-1, 1}, 
                    {0, -1},         {0, 1}, 
                    {1, -1}, {1, 0}, {1, 1}};

            for (auto &d : dirs)
            {
                int nx = cx + d[0];
                int ny = cy + d[1];

                //
                if (nx < 0 || ny < 0 || nx >= width || ny >= height)
                    continue;

                Cell &neighbor = cells[ny][nx];
                if (!neighbor.isRevealed() && !neighbor.isMine())
                {
                    handleClick(nx * cellSize + 1, ny * cellSize + 1, false);
                }
            }
        }
    }
}
