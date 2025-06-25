#include "TestEmitterSystem.hpp"
#include <iostream>
#include "Logger.hpp"

using namespace ecs;

void TestEmitterSystem::update(ECSWorld &world, float dt)
{
    static bool emitted = false;
    if (!emitted)
    {
        LOG_INFO("[TestEmitterSystem] Emitting TestEvent with value 42");
        world.getEventBus().emit(TestEvent{42});
        emitted = true;
    }
}