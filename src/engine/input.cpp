#include "input.hpp"
#include "core/game_state.hpp"
#include "entities/ball.hpp"

void ProcessInput()
{
    GameState::GetInstance().ball->Move();
}