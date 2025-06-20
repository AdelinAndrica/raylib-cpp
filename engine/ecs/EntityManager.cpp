#include "EntityManager.hpp"

EntityManager::EntityManager()
    : nextID(0)
{
}

EntityID EntityManager::createEntity()
{
    EntityID id;
    if (!freeIDs.empty())
    {
        id = freeIDs.front();
        freeIDs.pop();
        active[id] = true;
    }
    else
    {
        id = nextID++;
        active.push_back(true);
    }
    return id;
}

void EntityManager::destroyEntity(EntityID id)
{
    if (id >= active.size() || !active[id])
        return;
    active[id] = false;
    freeIDs.push(id);
}

bool EntityManager::isValid(EntityID id) const
{
    return id < active.size() && active[id];
}

void EntityManager::reset()
{
    nextID = 0;
    std::queue<EntityID> empty;
    std::swap(freeIDs, empty);
    active.clear();
}

std::size_t EntityManager::livingEntities() const
{
    std::size_t count = 0;
    for (bool a : active)
        if (a)
            ++count;
    return count;
}