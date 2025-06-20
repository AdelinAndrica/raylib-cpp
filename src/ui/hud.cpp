#include "hud.hpp"
#include "core/game_state.hpp"


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

}

void HUD::ShowMessage(const std::string &message)
{
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();
    DrawText(message.c_str(), screenW / 2 - MeasureText(message.c_str(), 20) / 2, screenH / 2, 20, DARKGRAY);
}