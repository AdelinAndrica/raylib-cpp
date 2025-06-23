// engine/ecs/SystemManager.cpp
#include "ecs/SystemManager.hpp"
#include "ecs/System.hpp" // <- Necesită pentru std::shared_ptr<ISystem> si SystemPhase

using namespace ecs;

void SystemManager::updateAll(ECSWorld &world, float dt, SystemPhase phase)
{
    auto it = systemsByPhase.find(phase);
    if (it != systemsByPhase.end())
    {
        for (auto &system : it->second)
        {
            system->update(world, dt);
        }
    }
}

void SystemManager::configure(ECSWorld &world)
{
    for (auto &[phase, systems] : systemsByPhase)
    {
        for (auto &system : systems)
        {
            system->configure(world);
        }
    }
}
