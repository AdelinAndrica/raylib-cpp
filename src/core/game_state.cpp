#include "core/game_state.hpp"
#include "levels/level.hpp"

GameState::GameState()
    : isGameOver(false),
      currentLevelIndex(0)
{
    levels.push_back(std::make_unique<Level>());
    levels.push_back(std::make_unique<Level>());
    levels.push_back(std::make_unique<Level>());
}

GameState &GameState::GetInstance()
{
    static GameState instance;
    return instance;
}

Level &GameState::GetCurrentLevel()
{
    return *levels[currentLevelIndex];
}

void GameState::ChangeLevel(int newIndex)
{
    if (newIndex > -1 && newIndex <= static_cast<int>(levels.size()))
    {
        currentLevelIndex = newIndex;
        levels[currentLevelIndex]->Load();
    }
    else
    {
        TraceLog(LOG_WARNING, "Invalid level index: %d", newIndex);
        isGameOver = true;
    }
}