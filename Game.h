#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Ball.h"
#include "Paddle.h"
#include "Block.h"
#include "Bonus.h"

class Game
{
private:
    sf::RenderWindow window;
    Paddle paddle;
    std::vector<Ball> balls;
    std::vector<Block> blocks;
    std::vector<Bonus> bonuses;
    bool bottomBonus;
    bool sticky;
    int score;
public:
    Game();
    void createBlocks();
    void events();
    void update();
    void render();
    void processBonuses();
    void run();
};
