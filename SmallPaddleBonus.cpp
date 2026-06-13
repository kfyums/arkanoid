#include "SmallPaddleBonus.h"
#include "Game.h"

SmallPaddleBonus::SmallPaddleBonus(float x, float y)
{
    shape.setRadius(10);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(x, y);
}

void SmallPaddleBonus::apply(Game& game)
{
    auto size = game.getPaddle().shape.getSize();
    game.getPaddle().shape.setSize(sf::Vector2f(size.x - 20, size.y));
}
