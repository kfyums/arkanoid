#include "Paddle.h"

Paddle::Paddle()
{
    shape.setSize(sf::Vector2f(120.f, 20.f));
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(340.f, 550.f);
}

void Paddle::moveLeft()
{
    if (shape.getPosition().x > 0)
        shape.move(-0.5f, 0);
}

void Paddle::moveRight()
{
    if (shape.getPosition().x + shape.getSize().x < 800.f)
        shape.move(0.5f, 0);
}
