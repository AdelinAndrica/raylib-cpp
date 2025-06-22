#pragma once

#include "ecs/System.hpp"
#include "ecs/ECSWorld.hpp"
#include "ecs/events/TestEvent.hpp"

class TestEmitterSystem : public ISystem
{
public:
    void update(ECSWorld &world, float dt) override;
    void configure(ECSWorld &world) override
    {
        // Nu este necesară configurarea suplimentară
    }
    SystemPhase phase() const override { return SystemPhase::Init; }
    std::string name() const override { return "TestEmitterSystem"; }
};