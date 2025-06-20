#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "EntityManager.hpp"

TEST_CASE("EntityManager basic creation and validation", "[EntityManager]")
{
    EntityManager em;

    SECTION("New entity is valid")
    {
        EntityID e1 = em.createEntity();
        REQUIRE(em.isValid(e1));
        REQUIRE(em.livingEntities() == 1);
    }

    SECTION("Destroyed entity is invalid")
    {
        EntityID e1 = em.createEntity();
        em.destroyEntity(e1);
        REQUIRE_FALSE(em.isValid(e1));
        REQUIRE(em.livingEntities() == 0);
    }

    SECTION("Destroyed entities recycle IDs")
    {
        EntityID e1 = em.createEntity();
        em.destroyEntity(e1);
        EntityID e2 = em.createEntity();
        REQUIRE(e1 == e2);
        REQUIRE(em.isValid(e2));
        REQUIRE(em.livingEntities() == 1);
    }

    SECTION("Invalid destroy does not crash or change state")
    {
        EntityID e1 = em.createEntity();
        em.destroyEntity(e1);
        em.destroyEntity(e1); // double destroy should be safe
        REQUIRE_FALSE(em.isValid(e1));
        REQUIRE(em.livingEntities() == 0);
    }

    SECTION("Reset removes all entities and frees IDs")
    {
        EntityID e1 = em.createEntity();
        EntityID e2 = em.createEntity();
        em.reset();
        REQUIRE_FALSE(em.isValid(e1));
        REQUIRE_FALSE(em.isValid(e2));
        REQUIRE(em.livingEntities() == 0);
        EntityID e3 = em.createEntity();
        REQUIRE(e3 == 0); // IDs restart from 0
    }
}