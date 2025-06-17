#include "raylib.h"
#include "ball.hpp"
#include "obstacle.hpp"
#include "hud.hpp"
#include "game_state.hpp"
#include <memory>

int main()
{
    InitWindow(800, 600, "Mingea se misca!");
    SetTargetFPS(60);

    Ball ball;
    HUD hud;
    GameState gameState;
    std::unique_ptr<Obstacle> obstacle = nullptr;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (gameState.isGameOver)
        {
            DrawText("Game Over! Press R to restart.", 250, 280, 20, RED);
            if (IsKeyPressed(KEY_R))
            {
                gameState.Reset();
                hud.Reset();
                obstacle.reset(); // Reset the obstacle
            }
        }
        else
        {
            // Handle input and update game state
            ball.Move(GetKeyPressed());
            if (obstacle)
            {
                if (obstacle->CheckCollision(ball.position, ball.radius))
                {
                    hud.lives--;
                    if (hud.lives <= 0)
                    {
                        gameState.isGameOver = true;
                    }
                }
            }

            // Draw the ball and HUD
            ball.Draw();
            hud.Draw();

            // Draw the obstacle if it exists
            if (obstacle)
            {
                obstacle->Draw();
            }

            // Check for collisions with window boundaries
            if (ball.position.x < ball.radius || ball.position.x > GetScreenWidth() - ball.radius ||
                ball.position.y < ball.radius || ball.position.y > GetScreenHeight() - ball.radius)
            {
                gameState.isGameOver = true;
            }
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}