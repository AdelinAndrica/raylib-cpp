#include "game_state.hpp"

void InitGameState()
{
    GameState &gs = GameState::GetInstance();
    gs.currentMap = std::make_unique<Map>(10, 10, 100); // hartă 10x10
    gs.player = std::make_unique<Player>(
        Vector2{1.0f * 100, 1.0f * 100}, // start pe tile (1,1), presupunând tileSize=32
        200.0f,                        // viteză
        100.0f,                         // tileSize
        "Hero");
}