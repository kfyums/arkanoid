#pragma once
#include "Bonus.h"

class SmallPaddleBonus : public Bonus
{
public:
    SmallPaddleBonus(float x, float y);
    void apply(Game& game) override;
};
