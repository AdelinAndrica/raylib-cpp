#include "game_state.hpp"
#include "engine/collision_system.hpp"

void GameState::Init()
{
    GameState &gs = GameState::GetInstance();
    gs.currentMap = std::make_unique<Map>(10, 10, 100);
    gs.player = std::make_unique<Player>(
        Vector2{1.0f * 100, 1.0f * 100},
        200.0f,
        100.0f,
        "Hero");
    gs.entities.clear();
    gs.entities.push_back(gs.player.get());
}

void GameState::Update()
{
    for (auto *e : entities)
        e->Update();
    CollisionSystem::Update(*currentMap, entities);
}

void GameState::Draw()
{
    if (currentMap)
        currentMap->Draw();
    for (auto *e : entities)
        e->Draw();
}