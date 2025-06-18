#include "level.hpp"
#include "raylib.h"

Level::Level()
{
    // Initialize level properties here
}

Level::~Level()
{
}

void Level::Load()
{
    Obstacles.clear();

    // Exemplu: Spawnează 3 obstacole cu checkpoint-uri
    auto obs1 = std::make_unique<Obstacle>(Vector2{200, 150}, 100, 40, BLUE);
    obs1->checkpoint = std::make_unique<Checkpoint>(Vector2{250, 100}, 20, GREEN);

    auto obs2 = std::make_unique<Obstacle>(Vector2{400, 300}, 120, 50, DARKBLUE);
    obs2->checkpoint = std::make_unique<Checkpoint>(Vector2{460, 270}, 20, GREEN);

    auto obs3 = std::make_unique<Obstacle>(Vector2{600, 400}, 80, 60, SKYBLUE);
    obs3->checkpoint = std::make_unique<Checkpoint>(Vector2{640, 470}, 20, GREEN);

    Obstacles.push_back(std::move(obs1));
    Obstacles.push_back(std::move(obs2));
    Obstacles.push_back(std::move(obs3));
}

void Level::Draw()
{
    for (const auto &obs : Obstacles)
        obs->Draw();
}

void Level::Update()
{
    // Update level logic here
}