#ifndef NumCELL_H
#define NumCELL_H

#include "cell.h"

class NumCell : public Cell
{
private:
    int adjacentMines = 0;

public:
    NumCell(int x, int y, float size);

    bool isMine() const override;
    void setAdjacentMines(int n) override;
    int getAdjacentMines() const override;
    void reveal() override;
    void setColour() override;
};

#endif
