#include "BottomBonus.h"
#include "Game.h"

BottomBonus::BottomBonus(float x, float y)
{
    shape.setRadius(10);
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(x, y);
}

void BottomBonus::apply(Game& game)
{
    game.setBottomBonus(true);
}
