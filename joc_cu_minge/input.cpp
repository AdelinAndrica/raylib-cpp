#include "input.hpp"
#include "raylib.h"

void ProcessInput(Ball &ball)
{
    if (IsKeyDown(KEY_RIGHT))
        ball.Move(KEY_RIGHT);
    if (IsKeyDown(KEY_LEFT))
        ball.Move(KEY_LEFT);
    if (IsKeyDown(KEY_UP))
        ball.Move(KEY_UP);
    if (IsKeyDown(KEY_DOWN))
        ball.Move(KEY_DOWN);
}