#include "Ball.h"

Ball::Ball()
{
    shape.setRadius(10);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(400, 300);
    speed.x = 0.15f;
    speed.y = -0.15f;
}

void Ball::move()
{
    shape.move(speed);
}
