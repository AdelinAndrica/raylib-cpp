#pragma once
#include <unordered_map>
#include <vector>
#include "Entity.hpp"
#include "Component.hpp"
#include "System.hpp"

class ECSRegistry
{
public:
    Entity createEntity();
    void destroyEntity(Entity entity);

    template <typename T, typename... Args>
    T &addComponent(Entity entity, Args &&...args);

    template <typename T>
    T *getComponent(Entity entity);

    void addSystem(System *system);
    void updateSystems(float dt);

private:
    EntityID nextID = 1;
    // Map entity --> components, map typeid --> components etc. (de completat la implementare)
    std::vector<System *> systems;
};