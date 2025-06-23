// MovementSystem.hpp
#pragma once

#include "ecs/System.hpp"
#include "ecs/ECSWorld.hpp"

class MovementSystem : public ISystem
{
public:
    void update(ecs::ECSWorld &world, float dt) override;
    void configure(ecs::ECSWorld &world) override
    {
        // Nu este necesară configurarea suplimentară
    }
    SystemPhase phase() const override { return SystemPhase::Update; }
    std::string name() const override { return "MovementSystem"; }
};
