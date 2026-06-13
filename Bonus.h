#pragma once
#include <SFML/Graphics.hpp>

class Game; 
class Bonus
{
public:
    sf::CircleShape shape;
    bool active = true;
    virtual ~Bonus() = default;
    virtual void move();
    virtual void apply(Game& game) = 0;
};
