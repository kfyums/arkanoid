#include "Block.h"
#include <cstdlib>

Block::Block(float x, float y)
{
    shape.setSize(sf::Vector2f(70, 30));
    shape.setPosition(x, y);
    hp = rand() % 3 + 1;
    unbreakable = rand() % 10 == 0;
    bonus = rand() % 5 == 0;
    speedBlock = rand() % 6 == 0;
    alive = true;
    if (unbreakable)
        shape.setFillColor(sf::Color::Black);
    else if (speedBlock)
        shape.setFillColor(sf::Color::Magenta);
    else if (bonus)
        shape.setFillColor(sf::Color::Green);
    else
        shape.setFillColor(sf::Color::Yellow);
}
