#include "Game.h"
#include <ctime>
#include <cstdlib>
#include <cmath>
#include "BigPaddleBonus.h"
#include "SmallPaddleBonus.h"
#include "SpeedBonus.h"
#include "StickyBonus.h"
#include "BottomBonus.h"

Game::Game()
    : window(sf::VideoMode((unsigned)WINDOW_WIDTH, (unsigned)WINDOW_HEIGHT), "Arkanoid")
{
    srand((unsigned)time(nullptr));
    createBlocks();
    balls.push_back(Ball());
    bottomBonus = false;
    sticky = false;
    score = 0;
}
float Game::getWidth() const { return WINDOW_WIDTH; }
float Game::getHeight() const { return WINDOW_HEIGHT; }
Paddle& Game::getPaddle() { return paddle; }
std::vector<Ball>& Game::getBalls() { return balls; }
void Game::setSticky(bool value) { sticky = value; }
void Game::setBottomBonus(bool value) { bottomBonus = value; }
void Game::createBlocks()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            blocks.emplace_back(j * 75 + 20, i * 40 + 20);
        }
    }
}

void Game::events()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        paddle.moveLeft();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        paddle.moveRight();
}

void Game::update()
{
    for (auto& ball : balls)
    {
        ball.move();
        if (ball.shape.getPosition().x <= 0 ||
            ball.shape.getPosition().x >= WINDOW_WIDTH - 20)
        {
            ball.speed.x = -ball.speed.x;
        }
        if (ball.shape.getPosition().y <= 0)
        {
            ball.speed.y = -ball.speed.y;
        }
        if (ball.shape.getGlobalBounds().intersects(paddle.shape.getGlobalBounds()))
        {
            if (sticky)
            {
                ball.speed = {0.f, 0.f};
                ball.shape.setPosition(
                    paddle.shape.getPosition().x + 50,
                    paddle.shape.getPosition().y - 20
                );
            }
            else
            {
                ball.speed.y = -std::abs(ball.speed.y);
            }
        }
        for (auto& block : blocks)
        {
            if (!block.alive) continue;
            if (ball.shape.getGlobalBounds().intersects(block.shape.getGlobalBounds()))
            {
                ball.speed.y = -ball.speed.y;

                if (block.speedBlock)
                {
                    ball.speed *= 1.2f;
                }
                if (!block.unbreakable)
                {
                    block.hp--;
                    score++;
                    if (block.bonus && rand() % 2 == 0)
                    {
                        int t = rand() % 5;
                        std::unique_ptr<Bonus> bonus;
                        switch (t)
                        {
                        case 0:
                            bonus = std::make_unique<BigPaddleBonus>(block.shape.getPosition().x, block.shape.getPosition().y);
                            break;
                        case 1:
                            bonus = std::make_unique<SmallPaddleBonus>(block.shape.getPosition().x, block.shape.getPosition().y);
                            break;
                        case 2:
                            bonus = std::make_unique<SpeedBonus>(block.shape.getPosition().x, block.shape.getPosition().y);
                            break;
                        case 3:
                            bonus = std::make_unique<StickyBonus>(block.shape.getPosition().x, block.shape.getPosition().y);
                            break;
                        case 4:
                            bonus = std::make_unique<BottomBonus>(block.shape.getPosition().x, block.shape.getPosition().y);
                            break;
                        }
                        bonuses.push_back(std::move(bonus));
                    }

                    if (block.hp <= 0)
                    {
                        block.alive = false;
                        score += 5;
                    }
                }
            }
        }

        if (ball.shape.getPosition().y > WINDOW_HEIGHT)
        {
            if (bottomBonus)
            {
                bottomBonus = false;
                ball.speed.y = -std::abs(ball.speed.y);
            }
            else
            {
                ball.shape.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
                ball.speed = {0.3f, -0.3f};
            }
        }
    }
    processBonuses();
    cleanup();
}

void Game::processBonuses()
{
    for (auto& bonus : bonuses)
    {
        if (!bonus->active) continue;
        bonus->move();
        if (bonus->shape.getGlobalBounds().intersects(paddle.shape.getGlobalBounds()))
        {
            bonus->active = false;
            bonus->apply(*this);
        }
    }
}

void Game::cleanup()
{
    bonuses.erase(
        std::remove_if(bonuses.begin(), bonuses.end(),
            [](const std::unique_ptr<Bonus>& b)
            {
                return !b->active;
            }),
        bonuses.end()
    );
    blocks.erase(
        std::remove_if(blocks.begin(), blocks.end(),
            [](const Block& b)
            {
                return !b.alive;
            }),
        blocks.end()
    );
}
void Game::render()
{
    window.clear(sf::Color::White);

    window.draw(paddle.shape);

    for (auto& ball : balls)
        window.draw(ball.shape);

    for (auto& block : blocks)
        window.draw(block.shape);

    for (auto& bonus : bonuses)
        window.draw(bonus->shape);

    window.display();
}
void Game::run()
{
    while (window.isOpen())
    {
        events();
        update();
        render();
    }
}
