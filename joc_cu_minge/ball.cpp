#include "ball.hpp"
#include <cmath>
#include <algorithm>
#include "raylib.h"
#include "collision_system.hpp"

Ball::Ball(Vector2 pos, float r, float s, Vector2 v, float a, float f)
    : position(pos), radius(r), speed(s), velocity(v), acceleration(a), friction(f)
{
    if (radius == 0.0f)
        radius = 40.0f;
    if (speed == 0.0f)
        speed = 300.0f;
    if (acceleration == 0.0f)
        acceleration = 1000.0f;
    if (friction == 0.0f)
        friction = 0.98f;
}

Ball::Ball()
{
    position = {400, 300};
    velocity = {0, 0};
    radius = 40.0f;
    speed = 300.0f;
    acceleration = 1000.0f;
    friction = 0.98f;
}
void Ball::Move()
{
    float dt = GetFrameTime();

    // Input
    if (IsKeyDown(KEY_RIGHT))
        velocity.x += acceleration * dt;
    if (IsKeyDown(KEY_LEFT))
        velocity.x -= acceleration * dt;
    if (IsKeyDown(KEY_DOWN))
        velocity.y += acceleration * dt;
    if (IsKeyDown(KEY_UP))
        velocity.y -= acceleration * dt;

    // Friction (exponențială)
    velocity.x *= powf(friction, dt * 60);
    velocity.y *= powf(friction, dt * 60);

    // Clamp to speed
    if (velocity.x > speed)
        velocity.x = speed;
    if (velocity.x < -speed)
        velocity.x = -speed;
    if (velocity.y > speed)
        velocity.y = speed;
    if (velocity.y < -speed)
        velocity.y = -speed;

    // Update position
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    // Check for window collision and stop at edges and reverse direction while maintaining physics
    if (CollisionSystem::CheckBallWindowCollision(*this))
    {
        // Reverse direction on collision
        if (position.x - radius < 0 || position.x + radius > GetScreenWidth())
            velocity.x *= -1;
        if (position.y - radius < 0 || position.y + radius > GetScreenHeight())
            velocity.y *= -1;

        // Clamp position to window edges
        position.x = std::clamp(position.x, radius, static_cast<float>(GetScreenWidth()) - radius);
        position.y = std::clamp(position.y, radius, static_cast<float>(GetScreenHeight()) - radius);
    }
}

void Ball::Draw() const
{
    DrawCircleV(position, radius, RED);
}
