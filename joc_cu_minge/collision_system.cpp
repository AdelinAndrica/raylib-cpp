#include "collision_system.hpp"

Obstacle *CollisionSystem::CheckBallObstacleCollision(const Ball &ball, const std::vector<std::unique_ptr<Obstacle>> &obstacles)
{
    for (const auto &obs : obstacles)
    {
        if (obs->CheckCollision(ball.position, ball.radius))
            return obs.get();
    }
    return nullptr;
}

Checkpoint *CollisionSystem::CheckBallCheckpointCollision(const Ball &ball, const std::vector<std::unique_ptr<Obstacle>> &obstacles)
{
    for (const auto &obs : obstacles)
    {
        if (obs->checkpoint && obs->checkpoint->isActive)
        {
            if (obs->checkpoint->CheckCollision(ball.position, ball.radius))
                return obs->checkpoint.get();
        }
    }
    return nullptr;
}