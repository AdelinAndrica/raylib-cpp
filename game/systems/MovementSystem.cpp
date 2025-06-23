// game/systems/MovementSystem.cpp
#include "MovementSystem.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"

using namespace ecs;

void MovementSystem::update(ECSWorld &world, float dt)
{
    world.view<Position, Velocity>([dt](Entity e, Position &pos, Velocity &vel)
                                   {
        pos.x += vel.dx * dt;
        pos.y += vel.dy * dt; });
}
