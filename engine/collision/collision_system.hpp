#pragma once
#include <vector>
#include "world/map.hpp"
#include "entities/entity.hpp"

class CollisionSystem
{
public:
    // Procesează toate entitățile (nu doar player)
    static void Update(Map &map, std::vector<Entity *> &entities);

private:
    static void HandleTransitionTile(Map &map, Entity *entity, int tileX, int tileY, TileType type, int transitionTarget);
};