#include "Core.hpp"
#include "ResourceManager.hpp"
#include "AudioManager.hpp"
#include "InputManager.hpp"
#include "ConfigManager.hpp"
#include "AssetWatcher.hpp"
#include "assets/AssetPipeline.hpp"
#include "assets/IAssetProcessor.hpp"
#include "assets/ImageAssetProcessor.hpp"
#include "assets/SoundAssetProcessor.hpp"
#include "utils/Utils.hpp"

Core::Core()
{
    world = std::make_unique<ecs::ECSWorld>();
    resources = std::make_unique<ResourceManager>();
    audio = std::make_unique<AudioManager>(this);
    input = std::make_unique<InputManager>();
    config = std::make_unique<ConfigManager>();

    pipeline = std::make_unique<AssetPipeline>();
    pipeline->RegisterProcessor(std::make_shared<ImageAssetProcessor>());
    pipeline->RegisterProcessor(std::make_shared<SoundAssetProcessor>());

    assetWatcher = std::make_unique<AssetWatcher>("assets");
    assetWatcher->OnChange([this](const std::string &path)
                           {
        if (pipeline->ProcessAsset(path)) {
            // După procesare, hot-reload resursa dacă e cazul
            if (Utils::EndsWith(path, ".png")) resources->ReloadTexture(path);
            else if (Utils::EndsWith(path, ".ttf")) resources->ReloadFont(path);
            else if (Utils::EndsWith(path, ".wav")) resources->ReloadSound(path);
            else if (Utils::EndsWith(path, ".ogg")) resources->ReloadMusic(path);
        } });
    assetWatcher->Start();
}

Core::~Core()
{
    if (assetWatcher)
        assetWatcher->Stop();
}
