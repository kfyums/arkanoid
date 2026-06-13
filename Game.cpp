#include "Game.h"
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <algorithm>

Game::Game()
    : window(sf::VideoMode(800, 600), "Arkanoid")
{
    srand((unsigned)time(nullptr));
    createBlocks();
    balls.push_back(Ball());
    bottomBonus = false;
    sticky = false;
    score = 0;
}

void Game::createBlocks()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            blocks.push_back(Block(j * 75 + 20, i * 40 + 20));
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
        ball.shape.move(ball.speed);
        if (ball.shape.getPosition().x <= 0.f ||
            ball.shape.getPosition().x >= 780.f)
        {
            ball.speed.x = -ball.speed.x;
        }
        if (ball.shape.getPosition().y <= 0.f)
        {
            ball.speed.y = std::abs(ball.speed.y);
        }
        if (ball.shape.getGlobalBounds().intersects(paddle.shape.getGlobalBounds()))
        {
            if (sticky)
            {
                ball.speed = { 0.f, 0.f };
                ball.shape.setPosition(  paddle.shape.getPosition().x + 50.f, 530.f  );
            }
            else
            {
                float hitPos =  (ball.shape.getPosition().x - paddle.shape.getPosition().x) / paddle.shape.getSize().x;
                ball.speed.x = (hitPos - 0.5f) * 0.8f;
                ball.speed.y = -std::abs(ball.speed.y);
            }
        }
        for (auto& block : blocks)
        {
            if (!block.alive)
                continue;
            if (ball.shape.getGlobalBounds().intersects(block.shape.getGlobalBounds()))
            {
                sf::Vector2f bPos = ball.shape.getPosition();
                sf::Vector2f blPos = block.shape.getPosition();
                float dx = bPos.x - blPos.x;
                float dy = bPos.y - blPos.y;
                if (std::abs(dx) > std::abs(dy))
                    ball.speed.x = -ball.speed.x;
                else
                    ball.speed.y = -ball.speed.y;
                if (block.speedBlock)
                {
                    ball.speed.x += (ball.speed.x > 0 ? 0.03f : -0.03f);
                    ball.speed.y += (ball.speed.y > 0 ? 0.03f : -0.03f);
                }
                if (!block.unbreakable)
                {
                    block.hp--;
                    score++;
                    if (block.bonus && rand() % 2 == 0)
                    {
                        bonuses.push_back(
                            Bonus(
                                block.shape.getPosition().x,
                                block.shape.getPosition().y,
                                rand() % 5
                            )
                        );
                    }
                    if (block.hp <= 0)
                    {
                        block.alive = false;
                        block.shape.setPosition(-100.f, -100.f);
                    }
                }
            }
        }
        if (ball.shape.getPosition().y > 600.f)
        {
            if (bottomBonus)
            {
                bottomBonus = false;
                float hitPos = (ball.shape.getPosition().x - paddle.shape.getPosition().x) / paddle.shape.getSize().x;
                ball.speed.x = (hitPos - 0.5f) * 0.8f;
                ball.speed.y = -0.5f;
            }
            else
            {
                ball.shape.setPosition(400.f, 300.f);
                ball.speed = { 0.3f, -0.3f };
            }
        }
        float maxSpeed = 0.6f;

        ball.speed.x = std::clamp(ball.speed.x, -maxSpeed, maxSpeed);
        ball.speed.y = std::clamp(ball.speed.y, -maxSpeed, maxSpeed);
    }
    processBonuses();
}

void Game::processBonuses()
{
    for (auto& bonus : bonuses)
    {
        if (!bonus.active)
            continue;
        bonus.move();
        if (bonus.shape.getGlobalBounds().intersects(paddle.shape.getGlobalBounds()))
        {
            bonus.active = false;
            if (bonus.type == 0)
            {
                paddle.shape.setSize({   paddle.shape.getSize().x + 30.f, 20.f });
            }
            if (bonus.type == 1)
            {
                paddle.shape.setSize({std::max(30.f, paddle.shape.getSize().x - 20.f),20.f });
            }
            if (bonus.type == 2)
            {
                for (auto& ball : balls)
                {
                    ball.speed.x = (ball.speed.x > 0 ? 0.3f : -0.3f);
                    ball.speed.y = (ball.speed.y > 0 ? 0.3f : -0.3f);
                }
            }
            if (bonus.type == 3)
                sticky = true;
            if (bonus.type == 4)
                bottomBonus = true;
        }
    }
}

void Game::render()
{
    window.clear(sf::Color::White);
    window.draw(paddle.shape);
    for (auto& ball : balls)
        window.draw(ball.shape);
    for (auto& block : blocks)
        if (block.alive)
            window.draw(block.shape);
    for (auto& bonus : bonuses)
        if (bonus.active)
            window.draw(bonus.shape);
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

