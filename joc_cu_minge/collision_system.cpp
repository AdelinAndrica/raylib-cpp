#include "collision_system.hpp"

bool CollisionSystem::CheckSingleBallObstacleCollision(const Ball &ball, const Obstacle &obstacle)
{
    Rectangle rect = {obstacle.position.x, obstacle.position.y, (float)obstacle.width, (float)obstacle.height};
    return CheckCollisionCircleRec(ball.position, ball.radius, rect);
}

Obstacle *CollisionSystem::CheckBallObstacleCollision(const Ball &ball, const std::vector<std::unique_ptr<Obstacle>> &obstacles)
{
    for (const auto &obs : obstacles)
    {
        Rectangle rect = {obs->position.x, obs->position.y, (float)obs->width, (float)obs->height};
        if (CheckCollisionCircleRec(ball.position, ball.radius, rect))
        {
            return obs.get();
        }
    }
    return nullptr;
}

bool CollisionSystem::CheckSingleBallCheckpointCollision(const Ball &ball, const Checkpoint &checkpoint)
{
    return CheckCollisionCircleRec(ball.position, ball.radius, {checkpoint.position.x - checkpoint.radius, checkpoint.position.y - checkpoint.radius, checkpoint.radius * 2.0f, checkpoint.radius * 2.0f});
}

bool CollisionSystem::CheckRectangleRectangleCollision(Vector2 rect1Pos, float rect1Width, float rect1Height,
                                                       Vector2 rect2Pos, float rect2Width, float rect2Height)
{
    return !(rect1Pos.x + rect1Width < rect2Pos.x || rect2Pos.x + rect2Width < rect1Pos.x ||
             rect1Pos.y + rect1Height < rect2Pos.y || rect2Pos.y + rect2Height < rect1Pos.y);
}

bool CollisionSystem::CheckBallWindowCollision(const Ball &ball)
{
    float screenWidth = static_cast<float>(GetScreenWidth());
    float screenHeight = static_cast<float>(GetScreenHeight());

    // Check collision with window borders
    return (ball.position.x - ball.radius < 0.0f || ball.position.x + ball.radius > screenWidth ||
            ball.position.y - ball.radius < 0.0f || ball.position.y + ball.radius > screenHeight);
}

Checkpoint *CollisionSystem::CheckBallCheckpointCollision(const Ball &ball, const std::vector<std::unique_ptr<Obstacle>> &obstacles)
{
    for (const auto &obs : obstacles)
    {
        if (obs->checkpoint && obs->checkpoint->isActive)
        {
            if (CheckSingleBallCheckpointCollision(ball, *obs->checkpoint))
                return obs->checkpoint.get();
        }
    }
    return nullptr;
}