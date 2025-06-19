#include "checkpoint.hpp"
#include "systems/collision_system.hpp"

Checkpoint::Checkpoint(Vector2 pos, float r, Color c)
    : position(pos), radius(r), color(c), isActive(true) {}

void Checkpoint::Draw() const
{
    if (isActive)
        DrawCircleV(position, radius, color);
}

bool Checkpoint::CheckCollision()
{
    return CollisionSystem::CheckSingleBallCheckpointCollision(*this);
}

void Checkpoint::Destroy()
{
    isActive = false;
}