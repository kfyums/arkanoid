#include "BigPaddleBonus.h"
#include "Game.h"

BigPaddleBonus::BigPaddleBonus(float x, float y)
{
    shape.setRadius(10);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(x, y);
}

void BigPaddleBonus::apply(Game& game)
{
    auto size = game.getPaddle().shape.getSize();
    game.getPaddle().shape.setSize(sf::Vector2f(size.x + 30, size.y));
}
