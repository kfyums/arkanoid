#pragma once
#include <SFML/Graphics.hpp>

class Ball
{
public:
    sf::CircleShape shape;
    sf::Vector2f speed;
    Ball();
    void move();
};
