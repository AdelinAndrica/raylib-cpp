#include "raylib.h"
#include "ball.hpp"
#include "level.hpp"
#include "obstacle.hpp"
#include "hud.hpp"
#include "game_state.hpp"
#include "collision_system.hpp"
#include "gameplay_logic.hpp"
#include "input.hpp"
#include "npc.hpp"
#include <memory>
#include <iostream>

int main()
{
    InitWindow(800, 600, "Mingea se misca!");
    SetTargetFPS(60);

    HUD hud;
    GameState& gameState = GameState::GetInstance();
    std::unique_ptr<Level> level = std::make_unique<Level>();
    level->Load();

    while (!WindowShouldClose())
    {
        if (!gameState.isGameOver)
        {
            ProcessInput();
            HandleGameplayLogic(*level, gameState);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (gameState.isGameOver)
        {
            DrawText("Game Over! Press R to restart.", 250, 280, 20, RED);
            if (IsKeyPressed(KEY_R))
            {
                gameState.Reset();
                level->Load(); // Reset level/obstacles
            }
        }
        else
        {
            level->Draw();
            hud.Draw(gameState);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}