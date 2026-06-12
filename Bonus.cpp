#include "Bonus.h"

Bonus::Bonus(float x, float y, int t)
{
    shape.setRadius(10);
    shape.setFillColor(sf::Color::Cyan);
    shape.setPosition(x, y);
    type = t;
    active = true;
}

void Bonus::move()
{
    shape.move(0, 0.2f);
}
