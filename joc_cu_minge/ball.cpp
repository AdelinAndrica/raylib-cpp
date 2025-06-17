#include "ball.hpp"
#include "raylib.h"

Ball::Ball(Vector2 pos, float r, float s)
    : position(pos), radius(r), speed(s) {}

void Ball::Move(int key)
{
    if (key == KEY_RIGHT)
        position.x += speed;
    if (key == KEY_LEFT)
        position.x -= speed;
    if (key == KEY_UP)
        position.y -= speed;
    if (key == KEY_DOWN)
        position.y += speed;
}

void Ball::Draw() const
{
    DrawCircleV(position, radius, RED);
}