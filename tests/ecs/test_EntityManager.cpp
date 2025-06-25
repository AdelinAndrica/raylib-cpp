#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "ecs/EntityManager.hpp"

TEST_CASE("EntityManager basic creation and validation", "[EntityManager]")
{
    EntityManager em;

    SECTION("New entity is valid")
    {
        Entity e1 = em.create();
        REQUIRE(em.isAlive(e1));
        REQUIRE(em.livingEntities() == 1);
    }

    SECTION("Destroyed entity is invalid")
    {
        Entity e1 = em.create();
        em.destroy(e1);
        REQUIRE_FALSE(em.isAlive(e1));
        REQUIRE(em.livingEntities() == 0);
    }

    SECTION("Destroyed entities recycle IDs")
    {
        Entity e1 = em.create();
        em.destroy(e1);
        Entity e2 = em.create();
        REQUIRE(e1 == e2);
        REQUIRE(em.isAlive(e2));
        REQUIRE(em.livingEntities() == 1);
    }

    SECTION("Invalid destroy does not crash or change state")
    {
        Entity e1 = em.create();
        em.destroy(e1);
        em.destroy(e1); // double destroy should be safe
        REQUIRE_FALSE(em.isAlive(e1));
        REQUIRE(em.livingEntities() == 0);
    }

    SECTION("Reset removes all entities and frees IDs")
    {
        Entity e1 = em.create();
        Entity e2 = em.create();
        em.reset();
        REQUIRE_FALSE(em.isAlive(e1));
        REQUIRE_FALSE(em.isAlive(e2));
        REQUIRE(em.livingEntities() == 0);
        Entity e3 = em.create();
        REQUIRE(e3 == 0); // IDs restart from 0
    }
}