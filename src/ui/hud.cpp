#include "hud.hpp"
#include "raylib.h"
#include <string>

HUD::HUD() {}

void HUD::Draw(const GameState &state) const
{
    const int hudWidth = 220;
    const int hudHeight = 120;
    const int padding = 20;
    const int screenW = GetScreenWidth();
    const int screenH = GetScreenHeight();
    const int hudX = screenW - hudWidth - padding;
    const int hudY = padding;

    // HUD background & border
    DrawRectangle(hudX, hudY, hudWidth, hudHeight, LIGHTGRAY);
    DrawRectangleLines(hudX, hudY, hudWidth, hudHeight, DARKGRAY);

    // Score
    DrawText("SCORE", hudX + 16, hudY + 10, 18, DARKGRAY);
    DrawText(TextFormat("%d", state.score), hudX + 120, hudY + 10, 24, BLACK);

    // Lives
    DrawText("LIVES", hudX + 16, hudY + 45, 18, DARKGRAY);
    for (int i = 0; i < state.lives; i++)
    {
        int cx = hudX + 90 + i * 28;
        int cy = hudY + 55;
        DrawCircle(cx, cy, 12, RED);
        DrawCircleLines(cx, cy, 12, DARKGRAY);
    }

    // Instructions
    DrawText("Use arrow keys", hudX + 16, hudY + 80, 16, GRAY);
    DrawText("to move the ball", hudX + 16, hudY + 100, 16, GRAY);
}

void HUD::ShowMessage(const std::string &message)
{
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();
    DrawText(message.c_str(), screenW / 2 - MeasureText(message.c_str(), 20) / 2, screenH / 2, 20, DARKGRAY);
}