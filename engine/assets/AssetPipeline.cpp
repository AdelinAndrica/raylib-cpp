#include "assets/AssetPipeline.hpp"

void AssetPipeline::RegisterProcessor(std::shared_ptr<IAssetProcessor> processor)
{
    processors.push_back(processor);
}

bool AssetPipeline::ProcessAsset(const std::string &path)
{
    for (auto &proc : processors)
    {
        if (proc->CanProcess(path))
        {
            bool ok = proc->Process(path);
            if (!ok)
                proc->Fallback(path);
            return ok;
        }
    }
    return false;
}