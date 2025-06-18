#include "checkpoint.hpp"
#include "collision_system.hpp"
#include "raylib.h"

Checkpoint::Checkpoint(Vector2 pos, float r, Color c)
    : position(pos), radius(r), color(c), isActive(true) {}

void Checkpoint::Draw() const
{
    if (isActive)
        DrawCircleV(position, radius, color);
}

bool Checkpoint::CheckCollision(const Ball &ball)
{
    // Assuming CheckBallCheckpointCollision should take ball, position, and radius.
    // If it actually expects a vector of obstacles, you need to pass that instead.
    if (isActive && CollisionSystem::CheckBallCheckpointCollision(ball, position))
    {
        Destroy();
        return true;
    }
    // If the function expects a vector, replace the above line with the correct arguments, e.g.:
    // if (isActive && CollisionSystem::CheckBallCheckpointCollision(ball, obstacles))
    return false;
}

void Checkpoint::Destroy()
{
    isActive = false;
}