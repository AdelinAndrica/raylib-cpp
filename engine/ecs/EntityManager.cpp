// engine/ecs/EntityManager.cpp
#include "ecs/EntityManager.hpp"
#include "Logger.hpp"

Entity EntityManager::create()
{
    Entity e = recycled.empty() ? next++ : recycled.back();
    if (!recycled.empty())
    {
        LOG_DEBUG("Recycled entity ID: " + std::to_string(e));
        recycled.pop_back();
    }
    alive.insert(e);
    LOG_INFO("Created entity: " + std::to_string(e));
    return e;
}

void EntityManager::destroy(Entity e)
{
    if (alive.erase(e))
    {
        recycled.push_back(e);
        LOG_INFO("Destroyed entity: " + std::to_string(e));
    }
    else
    {
        LOG_WARN("Tried to destroy non-existent entity: " + std::to_string(e));
    }
}

bool EntityManager::isAlive(Entity e) const
{
    return alive.find(e) != alive.end();
}

void EntityManager::reset()
{
    recycled.clear();
    alive.clear();
    next = 1;
    LOG_INFO("EntityManager reset");
}
