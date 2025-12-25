#ifndef MINE_H
#define MINE_H

#include "cell.h"

class Mine : public Cell
{
public:
    Mine(int x, int y, float size);

    void setRevealed(bool r) override;
    void setColour() override {};

    void print(std::ostream &os) const override
    {
        // IsMine(0) x y reveald flagged adjeacentmines
        os << 0 << ' ' << revealed << ' ' << flagged;
    }
};

#endif
