#pragma once
#include "raylib.h"
#include "ball.hpp"

class NPC
{
public:
    Vector2 position;
    float radius;
    Color color;
    Vector2 velocity;

    NPC(Vector2 pos, float r, Color col, Vector2 vel);

    void Move();
    void Draw() const;
    bool isPlayerNear(const Ball &ball);
    void startConversation();
    void checkConditions();
};