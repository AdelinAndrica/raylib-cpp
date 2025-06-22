// include/ecs/EntityManager.hpp
#pragma once

#include <unordered_set>
#include <vector>
#include <cstdint>

using Entity = std::uint32_t;

// =================== EntityManager ===================
class EntityManager {
public:
    EntityManager() = default;
    ~EntityManager() = default;
    Entity create();
    void destroy(Entity e);
    bool isAlive(Entity e) const;

private:
    Entity next = 1;
    std::vector<Entity> recycled;
    std::unordered_set<Entity> alive;
};
