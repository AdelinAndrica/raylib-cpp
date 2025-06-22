// include/ecs/ComponentStorage.hpp
#pragma once

#include <unordered_map>
#include <vector>
#include <cstdint>

using Entity = std::uint32_t;

// =================== ComponentStorage ===================
template <typename T>
class ComponentStorage
{
    std::unordered_map<Entity, T> components;

public:
    void add(Entity e, const T &c)
    {
        components[e] = c;
    }

    bool has(Entity e) const
    {
        return components.find(e) != components.end();
    }

    void remove(Entity e)
    {
        components.erase(e);
    }

    T &get(Entity e)
    {
        return components.at(e);
    }

    const std::unordered_map<Entity, T> &raw() const
    {
        return components;
    }

    std::vector<Entity> entities() const
    {
        std::vector<Entity> result;
        result.reserve(components.size());
        for (const auto &[e, _] : components)
        {
            result.push_back(e);
        }
        return result;
    }
};
