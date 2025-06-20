#include "core/game_state.hpp"
#include "entities/player.hpp"
#include "raylib.h"

int main()
{
    InitWindow(800, 600, "JRPG Example");
    InitGameState();

    GameState &gs = GameState::GetInstance();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the map
        if (gs.currentMap)
        {
            gs.currentMap->Draw();
        }
        gs.player->Update();
        gs.player->Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}