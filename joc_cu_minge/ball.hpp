#pragma once
#include "raylib.h"

class Ball
{
public:
    Vector2 position;
    float radius;
    float speed;

    Ball(Vector2 pos = {400, 300}, float r = 40.0f, float s = 5.0f);

    void Move(int key);
    void Draw() const;
};