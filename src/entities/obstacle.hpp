#pragma once
#include "raylib.h"
#include <memory>
#include "checkpoint.hpp"
#include "ball.hpp"

class Obstacle
{
public:
    Vector2 position;
    int width, height;
    Color color;
    std::unique_ptr<Checkpoint> checkpoint;

    Obstacle(Vector2 pos, int w, int h, Color c);

    void Draw() const;
    bool CheckCollision();
    bool isCompleted();
};