// include/ecs/System.hpp
#pragma once

#include "SystemPhase.hpp"
#include <string>

// =================== Forward declarations ===================
namespace ecs
{
    class ECSWorld; // Forward declaration pentru ECSWorld
}
// =================== ISystem ===================
class ISystem
{
public:
    virtual ~ISystem() = default;

    virtual void update(ecs::ECSWorld &world, float dt) = 0;
    virtual SystemPhase phase() const = 0;

    // opțional: nume pentru debugging / logging
    virtual std::string name() const { return "UnnamedSystem"; }

    // opțional: configurare sistem (apelată înainte de update)
    virtual void configure(ecs::ECSWorld &world) {}
};
