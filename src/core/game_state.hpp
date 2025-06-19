#pragma once
#include "raylib.h"
#include <vector>
#include <memory>

class Ball;
class Level;

struct GameState
{
    bool isGameOver = false;
    std::unique_ptr<Ball> ball;
    std::vector<std::unique_ptr<Level>> levels;

    // Current level index.
    int currentLevelIndex = 0;

    int score = 0;
    int lives = 3;

    GameState();
    ~GameState() = default;

    void Reset()
    {
        isGameOver = false;
        score = 0;
        lives = 3;
    }

    // Returns the current level.
    Level &GetCurrentLevel();

    // Changes to the specified level.
    void ChangeLevel(int levelIndex);

    // Returns the singleton instance of GameState.
    static GameState &GetInstance();
};