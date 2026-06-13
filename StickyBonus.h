#pragma once
#include "Bonus.h"

class StickyBonus : public Bonus
{
public:
    StickyBonus(float x, float y);
    void apply(Game& game) override;
};
