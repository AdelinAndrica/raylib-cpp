#include "LoggerSystem.hpp"
#include "Logger.hpp"
#include <iostream>

void LoggerSystem::configure(ecs::ECSWorld &world)
{
    world.getEventBus().subscribe<TestEvent>([](const TestEvent &event)
    {
        LOG_INFO("[LoggerSystem] Received TestEvent with value: " + std::to_string(event.value));
    });
}

void LoggerSystem::update(ecs::ECSWorld &world, float dt)
{
    // No-op
}