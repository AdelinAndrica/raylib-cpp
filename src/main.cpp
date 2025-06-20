#include "raylib.h"
#include "core/gameplay_logic.hpp"
#include "core/game_state.hpp"
#include "entities/npc.hpp"
#include "engine/input.hpp"
#include "systems/collision_system.hpp"
#include "ui/hud.hpp"
#include <memory>
#include <iostream>

int main()
{
    InitWindow(800, 600, "Mingea se misca!");
    SetTargetFPS(60);

    HUD hud;
    GameState &gameState = GameState::GetInstance();

    while (!WindowShouldClose())
    {
        if (!gameState.isGameOver)
        {
            ProcessInput();
            HandleGameplayLogic(gameState);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (gameState.isGameOver)
        {
            DrawText("Game Over! Press R to restart.", 250, 280, 20, RED);
            if (IsKeyPressed(KEY_R))
            {
                gameState.Reset();
            }
        }
        else
        {
            hud.Draw(gameState);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}