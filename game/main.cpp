// game/main.cpp
#include "ecs/ECSWorld.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "systems/MovementSystem.hpp"
#include "systems/LoggerSystem.hpp"
#include "systems/TestEmitterSystem.hpp"
#include <iostream>
#include <memory>

int main()
{
    ECSWorld world;

    // Register systems
    world.addSystem<TestEmitterSystem>(std::make_shared<TestEmitterSystem>(), SystemPhase::Init);
    world.addSystem<LoggerSystem>(std::make_shared<LoggerSystem>(), SystemPhase::Update);
    world.addSystem<MovementSystem>(std::make_shared<MovementSystem>(), SystemPhase::Update);

    world.configureSystems();

    // Create entity with components
    Entity player = world.createEntity();
    world.addComponent(player, Position{10.f, 20.f});
    world.addComponent(player, Velocity{5.f, 2.f});

    std::cout << "Before update:\n";
    world.view<Position>([](Entity e, Position &pos)
                         { std::cout << "Entity " << e << " has Position(" << pos.x << ", " << pos.y << ")\n"; });

    // Run systems
    world.updateSystems(0.016f, SystemPhase::Init);
    world.updateSystems(0.016f, SystemPhase::Update);

    std::cout << "After update:\n";
    world.view<Position>([](Entity e, Position &pos)
                         { std::cout << "Entity " << e << " has Position(" << pos.x << ", " << pos.y << ")\n"; });

    return 0;
}
