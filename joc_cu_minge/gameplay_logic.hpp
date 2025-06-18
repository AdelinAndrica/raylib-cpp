#pragma once
#include "ball.hpp"
#include "level.hpp"
#include "game_state.hpp"
#include "collision_system.hpp"

// Această funcție se ocupă de reacția la coliziuni și modifică gameState
void HandleGameplayLogic(Ball &ball, Level &level, GameState &gameState);