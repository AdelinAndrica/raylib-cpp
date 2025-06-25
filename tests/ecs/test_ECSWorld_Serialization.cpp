#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <ecs/ECSWorld.hpp>
#include <Position.hpp>
#include <Velocity.hpp>
#include <nlohmann/json.hpp>

using namespace ecs;

TEST_CASE("ECSWorld serialization/deserialization roundtrip", "[ecs][serialization]")
{
    ECSWorld world;
    Entity e1 = world.createEntity();
    Entity e2 = world.createEntity();
    world.addComponent<Position>(e1, Position{1.0f, 2.0f});
    world.addComponent<Velocity>(e1, Velocity{0.5f, 0.5f});
    world.addComponent<Position>(e2, Position{3.0f, 4.0f});

    nlohmann::json j = world.Serialize();

    ECSWorld loaded;
    loaded.Deserialize(j);

    // Check entities
    int count = 0;
    loaded.view<Position>([&](Entity e, Position pos)
                          {
        count++;
        if (pos.x == 1.0f) {
            REQUIRE(pos.y == 2.0f);
        } else if (pos.x == 3.0f) {
            REQUIRE(pos.y == 4.0f);
        } else {
            FAIL("Unexpected position value");
        } });
    REQUIRE(count == 2);

    // Check velocity
    int vcount = 0;
    loaded.view<Velocity>([&](Entity e, Velocity vel)
                          {
        vcount++;
        REQUIRE(vel.dx == 0.5f);
        REQUIRE(vel.dy == 0.5f); });
    REQUIRE(vcount == 1);
}