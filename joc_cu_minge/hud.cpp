#include "hud.hpp"
#include "raylib.h"

HUD::HUD() : score(0), lives(3) {}

void HUD::Draw() const
{
}

void HUD::Reset()
{
    score = 0;
    lives = 3;
}