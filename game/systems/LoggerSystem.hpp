#pragma once

#include "ecs/System.hpp"
#include "ecs/ECSWorld.hpp"
#include "ecs/events/TestEvent.hpp"

class LoggerSystem : public ISystem
{
public:
    void configure(ECSWorld &world) override;
    void update(ECSWorld &world, float dt) override;
    SystemPhase phase() const override { return SystemPhase::Render; }
    std::string name() const override { return "LoggerSystem"; }
};