#ifndef MINE_H
#define MINE_H

#include "cell.h"

class Mine : public Cell
{
public:
    Mine(int x, int y, float size);

    void reveal() override;
    void setColour() override {};
};

#endif
