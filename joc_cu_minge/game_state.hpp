#pragma once
#include "raylib.h"
#include "level.hpp"
#include "ball.hpp"
#include <vector>

struct GameState
{
    bool isGameOver = false;
    std::unique_ptr<Ball> ball;
    
    int score = 0;
    int lives = 3;

    std::vector<std::unique_ptr<Level>> levels;

    GameState() : isGameOver(false) {}
    void Reset()
    {
        isGameOver = false;
        score = 0;
        lives = 3;
    }
};