#pragma once
#include <SFML/Graphics.hpp>

class Bonus
{
public:
    sf::CircleShape shape;
    int type;
    bool active;
    Bonus(float x, float y, int t);
    void move();
};
