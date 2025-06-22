// game/systems/MovementSystem.cpp
#include "systems/MovementSystem.hpp"
#include "ecs/ECSWorld.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"

void MovementSystem::update(ECSWorld &world, float dt)
{
    world.view<Position, Velocity>([dt](Entity e, Position &pos, Velocity &vel)
                                   {
        pos.x += vel.dx * dt;
        pos.y += vel.dy * dt; });
}
