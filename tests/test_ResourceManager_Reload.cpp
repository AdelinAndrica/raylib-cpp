#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <ResourceManager.hpp>
#include <fstream>

TEST_CASE("ResourceManager reloads texture", "[ResourceManager][Reload]") {
    ResourceManager rm;
    // Creează un fișier PNG dummy (nu va fi valid, dar testăm fallback-ul)
    std::string path = "dummy.png";
    std::ofstream(path) << "not a real png";
    Texture2D &tex1 = rm.LoadTexture(path);
    REQUIRE(tex1.id == 0);

    // Simulează modificare și reload
    std::ofstream(path) << "changed";
    REQUIRE(rm.ReloadTexture(path));
    Texture2D &tex2 = rm.LoadTexture(path);
    REQUIRE(tex2.id == 0);

    std::remove(path.c_str());
}