#include "core/game_state.hpp"
#include "raylib.h"

int main()
{
    InitWindow(1920, 1080, "JRPG Example");

    GameState &gs = GameState::GetInstance();
    gs.Init(); // sau InitGameState();

    while (!WindowShouldClose())
    {
        gs.Update();

        BeginDrawing();
        gs.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}