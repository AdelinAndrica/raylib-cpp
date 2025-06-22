// include/ecs/SystemManager.hpp
#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include "ecs/SystemPhase.hpp" // <- Necesită pentru SystemPhase

class ISystem;  // Forward declaration
class ECSWorld; // Forward declaration
// =================== SystemManager ===================

class SystemManager
{
public:
    template <typename T>
    void registerSystem(std::shared_ptr<T> system, SystemPhase phase);

    void updateAll(ECSWorld &world, float dt, SystemPhase phase);
    void configure(ECSWorld &world);

private:
    std::unordered_map<SystemPhase, std::vector<std::shared_ptr<ISystem>>> systemsByPhase;
};

#include "ecs/System.hpp"

// =================== Template implementations ===================
template <typename T>
void SystemManager::registerSystem(std::shared_ptr<T> system, SystemPhase phase)
{
    static_assert(std::is_base_of<ISystem, T>::value, "T must derive from ISystem");
    systemsByPhase[phase].push_back(system);
}