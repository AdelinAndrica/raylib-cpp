#pragma once
#include "raylib.h"
#include "level.hpp"
#include <vector>

struct GameState
{
    bool isGameOver;
    Vector2 ballPosition;
    Vector2 ballVelocity;
    Vector2 paddlePosition;
    float paddleWidth;
    float paddleHeight;
    int score = 0;
    int lives = 3;

    std::vector<std::unique_ptr<Level>> levels;

    GameState() : isGameOver(false) {}
    void Reset() { isGameOver = false; }
};