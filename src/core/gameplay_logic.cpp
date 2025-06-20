#include "gameplay_logic.hpp"
#include "levels/level.hpp"
#include "game_state.hpp"
#include "systems/collision_system.hpp"
#include "entities/npc.hpp"

void HandleGameplayLogic(Level &level, GameState &gameState)
{
    level.Update();
    level.Npc->checkConditions();

}