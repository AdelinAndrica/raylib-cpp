#include "checkpoint.hpp"
#include "raylib.h"

Checkpoint::Checkpoint(Vector2 pos, float r, Color c)
    : position(pos), radius(r), color(c), isActive(true) {}

void Checkpoint::Draw() const
{
    if (isActive)
        DrawCircleV(position, radius, color);
}

bool Checkpoint::CheckCollision(const Vector2 &ballPos, float ballRadius)
{
    if (isActive && CheckCollisionCircles(ballPos, ballRadius, position, radius))
    {
        Destroy();
        return true;
    }
    return false;
}

void Checkpoint::Destroy()
{
    isActive = false;
}