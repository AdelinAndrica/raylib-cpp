#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <AudioManager.hpp>
#include <ResourceManager.hpp>
#include <Core.hpp>

struct DummyCore : public Core
{
    DummyCore()
    {
        resources = std::make_unique<ResourceManager>();
    }
};

TEST_CASE("AudioManager handles missing audio gracefully", "[AudioManager]")
{
    DummyCore core;
    AudioManager audio(&core);

    // Nu ar trebui să arunce sau să crape la fișiere lipsă
    REQUIRE_NOTHROW(audio.PlaySound("does_not_exist.wav"));
    REQUIRE_NOTHROW(audio.PlayMusic("does_not_exist.ogg"));
    REQUIRE_NOTHROW(audio.StopSound("does_not_exist.wav"));
    REQUIRE_NOTHROW(audio.StopMusic("does_not_exist.ogg"));
}