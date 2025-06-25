#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <assets/AssetPipeline.hpp>
#include <assets/ImageAssetProcessor.hpp>
#include <assets/SoundAssetProcessor.hpp>
#include <filesystem>
#include <fstream>
#include <thread>

// Safe remove cu retry pentru Windows/CI
inline void SafeRemove(const std::string &path)
{
    for (int i = 0; i < 10; ++i)
    {
        std::error_code ec;
        std::filesystem::remove(path, ec);
        if (!std::filesystem::exists(path))
            return;
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

TEST_CASE("AssetPipeline fallback for invalid image", "[AssetPipeline][Fallback]")
{
    AssetPipeline pipeline;
    auto imgProc = std::make_shared<ImageAssetProcessor>();
    pipeline.RegisterProcessor(imgProc);

    std::filesystem::create_directories("assets/fallback");
    if (!std::filesystem::exists("assets/fallback/fallback.png"))
    {
        std::ofstream("assets/fallback/fallback.png") << "PNG";
    }

    std::string path = "test_invalid.png";
    {
        std::ofstream(path) << "not a real png";
    }
    REQUIRE_FALSE(imgProc->Validate(path));
    pipeline.ProcessAsset(path);
    {
        std::ifstream f(path);
        std::string content;
        f >> content;
        REQUIRE(content == "PNG");
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    SafeRemove(path);
}

TEST_CASE("AssetPipeline fallback for invalid sound", "[AssetPipeline][Fallback]")
{
    AssetPipeline pipeline;
    auto sndProc = std::make_shared<SoundAssetProcessor>();
    pipeline.RegisterProcessor(sndProc);

    std::filesystem::create_directories("assets/fallback");
    if (!std::filesystem::exists("assets/fallback/fallback.wav"))
    {
        std::ofstream("assets/fallback/fallback.wav") << "WAV";
    }

    std::string path = "test_invalid.wav";
    {
        std::ofstream(path) << "not a real wav";
    }
    REQUIRE_FALSE(sndProc->Validate(path));
    pipeline.ProcessAsset(path);
    {
        std::ifstream f(path);
        std::string content;
        f >> content;
        REQUIRE(content == "WAV");
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    SafeRemove(path);
}