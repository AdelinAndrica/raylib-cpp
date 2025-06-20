#pragma once
#include "raylib.h"
#include <vector>
#include <memory>

class Level;

struct GameState
{
    bool isGameOver = false;
    std::vector<std::unique_ptr<Level>> levels;

    // Current level index.
    int currentLevelIndex = 0;

    GameState();
    ~GameState() = default;

    void Reset()
    {
        isGameOver = false;
    }

    // Returns the current level.
    Level &GetCurrentLevel();

    // Changes to the specified level.
    void ChangeLevel(int levelIndex);

    // Returns the singleton instance of GameState.
    static GameState &GetInstance();
};