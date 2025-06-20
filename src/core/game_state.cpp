#include "game_state.hpp"

void InitGameState()
{
    GameState &gs = GameState::GetInstance();
    gs.currentMap = std::make_unique<Map>(10, 10, 32); // hartă 10x10
    gs.player = std::make_unique<Player>(
        Vector2{1.0f * 32, 1.0f * 32}, // start pe tile (1,1), presupunând tileSize=32
        100.0f,                        // viteză
        32.0f,                         // tileSize
        "Hero");
}