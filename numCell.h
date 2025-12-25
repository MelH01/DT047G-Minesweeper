#ifndef NumCELL_H
#define NumCELL_H

#include "cell.h"

class NumCell : public Cell
{
private:
    int adjacentMines = 0;

public:
    NumCell(int x, int y, float size);

    void reveal() override;
    void setColour() override;

    void setAdjacentMines(int n) ;
    int getAdjacentMines() const ;
};

#endif
