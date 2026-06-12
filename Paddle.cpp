#include "Paddle.h"

Paddle::Paddle()
{
    shape.setSize(sf::Vector2f(120, 20));
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(340, 550);
}

void Paddle::moveLeft()
{
    shape.move(-0.5f, 0);
}

void Paddle::moveRight()
{
    shape.move(0.5f, 0);
}
