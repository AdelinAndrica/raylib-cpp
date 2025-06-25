#pragma once
#include <vector>
#include <memory>
#include <string>
#include "assets/IAssetProcessor.hpp"

class AssetPipeline {
public:
    void RegisterProcessor(std::shared_ptr<IAssetProcessor> processor);
    bool ProcessAsset(const std::string& path);

private:
    std::vector<std::shared_ptr<IAssetProcessor>> processors;
};