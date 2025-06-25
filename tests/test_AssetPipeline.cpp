#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <assets/AssetPipeline.hpp>
#include <fstream>
#include <filesystem>

class DummyProcessor : public IAssetProcessor
{
public:
    bool called = false;
    bool CanProcess(const std::string &path) const override { return path == "dummy.txt"; }
    bool Process(const std::string &path) override
    {
        called = true;
        return true;
    }
};

TEST_CASE("AssetPipeline calls correct processor", "[AssetPipeline]")
{
    AssetPipeline pipeline;
    auto proc = std::make_shared<DummyProcessor>();
    pipeline.RegisterProcessor(proc);

    std::ofstream("dummy.txt") << "test";
    REQUIRE(pipeline.ProcessAsset("dummy.txt"));
    REQUIRE(proc->called);

    std::filesystem::remove("dummy.txt");
}