#include "collision_system.hpp"
#include <iostream>

void CollisionSystem::Update(Map &map, std::vector<Entity *> &entities)
{
    for (auto *entity : entities)
    {
        int tx = entity->GetCurrentTileX();
        int ty = entity->GetCurrentTileY();

        // Coliziune cu pereți, dacă vrei generic
        // if (!map.isWalkable(tx, ty)) { ... }

        const Tile &tile = map.getTile(tx, ty);
        switch (tile.type)
        {
        case TileType::Door:
        case TileType::Edge:
        case TileType::Trigger:
            HandleTransitionTile(map, entity, tx, ty, tile.type, tile.transitionTarget);
            break;
        default:
            break;
        }
    }
}

void CollisionSystem::HandleTransitionTile(Map &map, Entity *entity, int tx, int ty, TileType type, int transitionTarget)
{
    // Fiecare entity poate avea propriul răspuns la trigger:

    entity->OnTrigger(type, transitionTarget);
}