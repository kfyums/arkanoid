#pragma once
#include <SFML/Graphics.hpp>

class Block
{
public:
    sf::RectangleShape shape;
    int hp;
    bool unbreakable;
    bool bonus;
    bool speedBlock;
    bool alive;
    Block(float x, float y);
};
