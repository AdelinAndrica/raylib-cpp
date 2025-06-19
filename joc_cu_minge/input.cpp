#include "input.hpp"
#include "raylib.h"
#include "game_state.hpp"

void ProcessInput()
{
    GameState::GetInstance().ball->Move();
}