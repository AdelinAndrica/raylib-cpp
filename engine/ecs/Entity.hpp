#pragma once
#include <cstdint>

using EntityID = std::uint32_t;

struct Entity
{
    EntityID id;
    explicit Entity(EntityID id_) : id(id_) {}
    bool operator==(const Entity &other) const { return id == other.id; }
};