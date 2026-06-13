#include "StickyBonus.h"
#include "Game.h"

StickyBonus::StickyBonus(float x, float y)
{
    shape.setRadius(10);
    shape.setFillColor(sf::Color::Magenta);
    shape.setPosition(x, y);
}

void StickyBonus::apply(Game& game)
{
    game.setSticky(true);
}
