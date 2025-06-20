#pragma once
#include "raylib.h"
#include <algorithm>
#include <string>

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
    bool isPlayerNear();
    void startConversation();
    void checkConditions();
};