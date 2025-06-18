#include "collision_system.hpp"

Obstacle *CollisionSystem::CheckBallObstacleCollision(const Ball &ball, const std::vector<std::unique_ptr<Obstacle>> &obstacles)
{
    for (const auto &obs : obstacles)
    {
        // Use the ball and the obstacle's properties
    }
    return nullptr;
}

bool CollisionSystem::CheckSingleBallObstacleCollision(const Ball &ball, const std::unique_ptr<Obstacle> &obstacle)
{
    Rectangle rect = {obstacle->position.x, obstacle->position.y, (float)obstacle->width, (float)obstacle->height};
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

void CollisionSystem::CheckBallWindowCollision(Ball &ball, int screenWidth, int screenHeight)
{
    // Check collision with left and right window borders
    if (ball.position.x - ball.radius < 0)
    {
        ball.position.x = ball.radius;
        ball.velocity.x *= -1;
    }
    else if (ball.position.x + ball.radius > screenWidth)
    {
        ball.position.x = screenWidth - ball.radius;
        ball.velocity.x *= -1;
    }

    // Check collision with top and bottom window borders
    if (ball.position.y - ball.radius < 0)
    {
        ball.position.y = ball.radius;
        ball.velocity.y *= -1;
    }
    else if (ball.position.y + ball.radius > screenHeight)
    {
        ball.position.y = screenHeight - ball.radius;
        ball.velocity.y *= -1;
    }
}

bool CollisionSystem::CheckRectangleRectangleCollision(Vector2 rect1Pos, float rect1Width, float rect1Height,
                                                       Vector2 rect2Pos, float rect2Width, float rect2Height)
{
    return !(rect1Pos.x + rect1Width < rect2Pos.x || rect2Pos.x + rect2Width < rect1Pos.x ||
             rect1Pos.y + rect1Height < rect2Pos.y || rect2Pos.y + rect2Height < rect1Pos.y);
}