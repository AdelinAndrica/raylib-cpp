#include "raylib.h"
#include "ball.hpp"
#include "level.hpp"
#include "obstacle.hpp"
#include "hud.hpp"
#include "game_state.hpp"
#include "collision_system.hpp"
#include "gameplay_logic.hpp"
#include "input.hpp"
#include <memory>

int main()
{
    InitWindow(800, 600, "Mingea se misca!");
    SetTargetFPS(60);

    Ball ball;
    HUD hud;
    GameState gameState;
    Level level;  // <-- Folosește Level
    level.Load(); // Populează Obstacles

    while (!WindowShouldClose())
    {
        if (!gameState.isGameOver)
        {
            ProcessInput(ball);
            HandleGameplayLogic(ball, level, gameState);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (gameState.isGameOver)
        {
            DrawText("Game Over! Press R to restart.", 250, 280, 20, RED);
            if (IsKeyPressed(KEY_R))
            {
                gameState.Reset();
                ball = Ball(); // Reset ball
                level.Load();  // Reset level/obstacles
            }
        }
        else
        {
            level.Draw();
            hud.Draw(gameState);
            ball.Draw();
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}