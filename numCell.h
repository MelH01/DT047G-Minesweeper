#ifndef NumCELL_H
#define NumCELL_H

#include "cell.h"

class NumCell : public Cell
{
private:
    int adjacentMines = 0;

public:
    NumCell(int x, int y, float size);

    void setRevealed(bool r) override;
    void setColour() override;

    void setAdjacentMines(int n);
    int getAdjacentMines() const;

    void print(std::ostream &os) const override
    {
        // NumCell(1) reveald flagged 
        os << 1 << ' ' << revealed << ' ' << flagged;
    }
};

#endif
