#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <Profiler.hpp>
#include <thread>

TEST_CASE("ProfilerScope logs duration", "[Profiler]")
{
    PROFILE_SCOPE("TestSleep");
    REQUIRE_NOTHROW([&]()
                    { std::this_thread::sleep_for(std::chrono::milliseconds(1)); }());
}