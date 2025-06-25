// engine/ecs/ECSWorld.cpp
#include "ecs/ECSWorld.hpp"
#include "ecs/EntityManager.hpp"
#include "Profiler.hpp"

using namespace ecs;

ECSWorld::ECSWorld()
{
    em = new EntityManager();
}

Entity ECSWorld::createEntity()
{
    return em->create();
}

void ECSWorld::destroyEntity(Entity e)
{
    em->destroy(e);
    for (auto &[_, storage] : storages)
    {
        auto remover = std::static_pointer_cast<IComponentRemover>(storage);
        remover->remove(e);
    }
}

bool ECSWorld::isAlive(Entity e) const
{
    return em->isAlive(e);
}

void ECSWorld::configureSystems()
{
    systemManager->configure(*this);
}

void ECSWorld::updateSystems(float dt, SystemPhase phase)
{
    PROFILE_SCOPE("ECSWorld::updateSystems");
    systemManager->updateAll(*this, dt, phase);
}

SystemManager &ECSWorld::getSystemManager()
{
    return *systemManager;
}
