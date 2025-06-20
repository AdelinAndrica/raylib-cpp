#include "obstacle.hpp"
#include "checkpoint.hpp"
#include "systems/collision_system.hpp"

Obstacle::Obstacle(Vector2 pos, int w, int h, Color c)
    : position(pos), width(w), height(h), color(c), checkpoint(nullptr) {}

void Obstacle::Draw() const
{
    DrawRectangleV(position, {static_cast<float>(width), static_cast<float>(height)}, color);
    if (checkpoint)
        checkpoint->Draw();
}

bool Obstacle::CheckCollision()
{
    // Folosim CollisionSystem
    return CollisionSystem::CheckSingleBallObstacleCollision(*this);
}

bool Obstacle::isCompleted()
{
    if (this->checkpoint)
        return false;
    return true;
}