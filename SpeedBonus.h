#pragma once
#include "Bonus.h"

class SpeedBonus : public Bonus
{
public:
    SpeedBonus(float x, float y);
    void apply(Game& game) override;
};
