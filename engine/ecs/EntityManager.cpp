// engine/ecs/EntityManager.cpp
#include "ecs/EntityManager.hpp"

Entity EntityManager::create()
{
    Entity e = recycled.empty() ? next++ : recycled.back();
    if (!recycled.empty())
        recycled.pop_back();
    alive.insert(e);
    return e;
}

void EntityManager::destroy(Entity e)
{
    alive.erase(e);
    recycled.push_back(e);
}

bool EntityManager::isAlive(Entity e) const
{
    return alive.find(e) != alive.end();
}
