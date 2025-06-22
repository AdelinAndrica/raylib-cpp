#include "TestEmitterSystem.hpp"
#include <iostream>

void TestEmitterSystem::update(ECSWorld &world, float dt)
{
    static bool emitted = false;
    if (!emitted)
    {
        std::cout << "[TestEmitterSystem] Emitting TestEvent with value 42\n";
        world.getEventBus().emit(TestEvent{42});
        emitted = true;
    }
}