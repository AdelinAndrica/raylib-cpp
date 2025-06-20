#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <ecs/ComponentManager.hpp>
#include <cstdint>
#include <vector>
#include <algorithm>

struct DummyComponent {
    int value;
    bool operator==(const DummyComponent& other) const { return value == other.value; }
};

using EntityID = std::uint32_t;

TEST_CASE("ComponentManager basic API and edge cases", "[ecs][ComponentManager]") {
    ecs::ComponentManager<DummyComponent, EntityID> cm;

    EntityID id1 = 100, id2 = 200, id3 = 300;

    SECTION("Add and get component") {
        cm.addComponent(id1, DummyComponent{42});
        REQUIRE(cm.hasComponent(id1));
        DummyComponent* comp = cm.getComponent(id1);
        REQUIRE(comp != nullptr);
        REQUIRE(comp->value == 42);
    }

    SECTION("Remove component and check absence") {
        cm.addComponent(id1, DummyComponent{99});
        cm.removeComponent(id1);
        REQUIRE_FALSE(cm.hasComponent(id1));
        REQUIRE(cm.getComponent(id1) == nullptr);
    }

    SECTION("Access non-existent component returns nullptr/false") {
        REQUIRE_FALSE(cm.hasComponent(id2));
        REQUIRE(cm.getComponent(id2) == nullptr);
        cm.removeComponent(id2); // should not throw or crash
    }

    SECTION("Re-add after removal") {
        cm.addComponent(id1, DummyComponent{11});
        cm.removeComponent(id1);
        cm.addComponent(id1, DummyComponent{22});
        DummyComponent* comp = cm.getComponent(id1);
        REQUIRE(comp != nullptr);
        REQUIRE(comp->value == 22);
    }

    SECTION("Multiple entities, all add/get/remove") {
        std::vector<EntityID> ids = {id1, id2, id3};
        for (auto id : ids) {
            cm.addComponent(id, DummyComponent{static_cast<int>(id)});
        }
        for (auto id : ids) {
            REQUIRE(cm.hasComponent(id));
            auto* comp = cm.getComponent(id);
            REQUIRE(comp != nullptr);
            REQUIRE(comp->value == static_cast<int>(id));
        }
        // Remove all
        for (auto id : ids) {
            cm.removeComponent(id);
            REQUIRE_FALSE(cm.hasComponent(id));
            REQUIRE(cm.getComponent(id) == nullptr);
        }
    }

    SECTION("Iterator and size reflect state") {
        REQUIRE(cm.size() == 0);
        cm.addComponent(id1, DummyComponent{1});
        cm.addComponent(id2, DummyComponent{2});
        cm.addComponent(id3, DummyComponent{3});
        REQUIRE(cm.size() == 3);

        std::vector<int> values;
        for (auto it = cm.begin(); it != cm.end(); ++it) {
            values.push_back(it->second.value);
        }
        std::sort(values.begin(), values.end());
        REQUIRE(values == std::vector<int>{1,2,3});
    }

    SECTION("Clear removes all components") {
        cm.addComponent(id1, DummyComponent{1});
        cm.addComponent(id2, DummyComponent{2});
        cm.clear();
        REQUIRE(cm.size() == 0);
        REQUIRE_FALSE(cm.hasComponent(id1));
        REQUIRE_FALSE(cm.hasComponent(id2));
    }

    SECTION("onEntityDestroyed removes only relevant component") {
        cm.addComponent(id1, DummyComponent{7});
        cm.addComponent(id2, DummyComponent{8});
        cm.onEntityDestroyed(id1);
        REQUIRE_FALSE(cm.hasComponent(id1));
        REQUIRE(cm.hasComponent(id2));
    }
}