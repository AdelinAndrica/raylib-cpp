#pragma once
#include "raylib.h"

class Checkpoint
{
public:
    Vector2 position;
    float radius;
    Color color;
    bool isActive;

    Checkpoint(Vector2 pos, float r, Color c);

    void Draw() const;
    bool CheckCollision();
    void Destroy();
};