#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <ConfigManager.hpp>
#include <fstream>

TEST_CASE("ConfigManager fallback and error handling", "[ConfigManager]")
{
    ConfigManager cfg;

    // Fallback la default
    REQUIRE(cfg.GetInt("not_found", 42) == 42);

    // Scrie un fișier corupt
    std::ofstream out("corrupt.ini");
    out << "not_a_valid_line\n";
    out << "key=123\n";
    out.close();

    REQUIRE(cfg.LoadFromFile("corrupt.ini"));
    REQUIRE(cfg.GetInt("key", 0) == 123);
    REQUIRE(cfg.GetInt("not_found", 99) == 99);
}