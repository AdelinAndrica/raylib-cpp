#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <ecs/EventBus.hpp>

struct DummyEvent
{
    int value;
};

TEST_CASE("EventBus subscribe and emit", "[EventBus]")
{
    EventBus bus;
    int called = 0;
    bus.subscribe<DummyEvent>([&](const DummyEvent &e)
                              { called += e.value; });

    bus.emit(DummyEvent{5});
    REQUIRE(called == 5);

    bus.emit(DummyEvent{3});
    REQUIRE(called == 8);
}