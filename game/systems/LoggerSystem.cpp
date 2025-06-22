#include "systems/LoggerSystem.hpp"
#include <iostream>

void LoggerSystem::configure(ECSWorld &world)
{
    world.getEventBus().subscribe<TestEvent>([](const TestEvent &event)
                                             { std::cout << "[LoggerSystem] Received TestEvent with value: " << event.value << "\n"; });
}

void LoggerSystem::update(ECSWorld &world, float dt)
{
    // No-op
}