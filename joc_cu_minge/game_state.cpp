#include "raylib.h"
#include "level.hpp"
#include "ball.hpp"
#include <vector>
#include "game_state.hpp"

GameState &GameState::GetInstance()
{
    static GameState instance;
    return instance;
}
