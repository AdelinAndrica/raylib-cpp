#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <AudioManager.hpp>
#include <Core.hpp>
#include <filesystem>

TEST_CASE("AudioManager handles missing audio gracefully", "[AudioManager]")
{
    std::filesystem::create_directories("assets/fallback");
    Core core;
    AudioManager audio(&core);

    // Sound inexistent
    REQUIRE_NOTHROW(audio.PlaySound("does_not_exist.wav"));
    REQUIRE_NOTHROW(audio.StopSound("does_not_exist.wav"));

    // Music inexistent
    REQUIRE_NOTHROW(audio.PlayMusic("does_not_exist.ogg"));
    REQUIRE_NOTHROW(audio.StopMusic("does_not_exist.ogg"));
}