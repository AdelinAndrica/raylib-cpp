#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <ResourceManager.hpp>
#include <raylib.h>

TEST_CASE("ResourceManager handles missing files gracefully", "[ResourceManager]")
{
    ResourceManager rm;

    // Textură inexistentă
    Texture2D &tex = rm.LoadTexture("does_not_exist.png");
    REQUIRE(tex.id == 0);

    // Font inexistent
    Font &font = rm.LoadFont("does_not_exist.ttf");
    REQUIRE(font.baseSize == 0);

    // Sound inexistent
    Sound &snd = rm.LoadSound("does_not_exist.wav");
    REQUIRE(snd.stream.buffer == nullptr);

    // Music inexistent
    Music &msc = rm.LoadMusic("does_not_exist.ogg");
    REQUIRE(msc.stream.buffer == nullptr);
}