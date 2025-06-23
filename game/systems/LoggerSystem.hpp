#pragma once

#include "ecs/System.hpp"
#include "ecs/ECSWorld.hpp"
#include "ecs/events/TestEvent.hpp"

class LoggerSystem : public ISystem
{
public:
    void configure(ecs::ECSWorld &world) override;
    void update(ecs::ECSWorld &world, float dt) override;
    SystemPhase phase() const override { return SystemPhase::Render; }
    std::string name() const override { return "LoggerSystem"; }
};