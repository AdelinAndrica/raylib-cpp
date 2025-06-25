#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <AssetWatcher.hpp>
#include <fstream>
#include <chrono>
#include <thread>
#include <atomic>
#include <filesystem>

TEST_CASE("AssetWatcher detects file changes", "[AssetWatcher]")
{
    using namespace std::filesystem;
    std::string testDir = "test_assets";
    create_directory(testDir);
    std::string testFile = testDir + "/test.txt";
    {
        std::ofstream f(testFile);
        f << "init";
        f.flush();
        f.close();
    }

    std::atomic<bool> changed = false;
    path expectedPath = absolute(testFile).lexically_normal();

    AssetWatcher watcher(testDir);
    watcher.OnChange([&](const std::string &pathStr)
                     {
        path changedPath = absolute(pathStr).lexically_normal();
        if (changedPath == expectedPath) changed = true; });
    watcher.Start();

    // Trigger change (scrie de două ori cu pauză pentru a forța timestamp nou)
    std::this_thread::sleep_for(std::chrono::milliseconds(700));
    {
        std::ofstream f(testFile);
        f << "changed";
        f.flush();
        f.close();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    {
        std::ofstream f(testFile);
        f << "changed again";
        f.flush();
        f.close();
    }

    // Așteaptă până la 5 secunde să se declanșeze callback-ul
    for (int i = 0; i < 50 && !changed; ++i)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    watcher.Stop();

    REQUIRE(changed == true);

    remove_all(testDir);
}