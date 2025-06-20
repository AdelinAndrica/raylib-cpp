#include "gameplay_logic.hpp"
#include "game_state.hpp"
#include "entities/npc.hpp"

void HandleGameplayLogic(GameState &gameState)
{
}

void CheckPlayerTransition(Map &map, Player &player)
{
    int tx = player.GetCurrentTileX();
    int ty = player.GetCurrentTileY();

    if (map.isTransition(tx, ty))
    {
        TileType tt = map.getTransitionType(tx, ty);
        int target = map.getTransitionTarget(tx, ty);
        switch (tt)
        {
        case TileType::Door:
            // ex: încarcă altă hartă/cameră, poziționează player-ul
            break;
        case TileType::Edge:
            // ex: teleport world map sau wrap
            break;
        case TileType::Trigger:
            // ex: pornește dialog/event
            break;
        default:
            break;
        }
    }
}