#pragma once
#include "Bonus.h"

class BottomBonus : public Bonus
{
public:
    BottomBonus(float x, float y);
    void apply(Game& game) override;
};
