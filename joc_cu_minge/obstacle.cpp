#include "obstacle.hpp"
#include "raylib.h"

Obstacle::Obstacle(Vector2 pos, int w, int h, Color c)
    : position(pos), width(w), height(h), color(c), checkpoint(nullptr) {}

void Obstacle::Draw() const
{
    DrawRectangleV(position, {static_cast<float>(width), static_cast<float>(height)}, color);
    if (checkpoint)
        checkpoint->Draw();
}

bool Obstacle::CheckCollision(const Vector2 &ballPos, float ballRadius)
{
    return CheckCollisionCircleRec(ballPos, ballRadius, {position.x, position.y, (float)width, (float)height});
}