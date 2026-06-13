#include "SpeedBonus.h"
#include "Game.h"

SpeedBonus::SpeedBonus(float x, float y)
{
    shape.setRadius(10);
    shape.setFillColor(sf::Color::Cyan);
    shape.setPosition(x, y);
}

void SpeedBonus::apply(Game& game)
{
    for (auto& ball : game.getBalls())
    {
        ball.speed.x *= 1.5f;
        ball.speed.y *= 1.5f;
    }
}
