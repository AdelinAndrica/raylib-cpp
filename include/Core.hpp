#pragma once

#include <memory>
#include "ecs/ECSWorld.hpp"
#include "ResourceManager.hpp"
#include "AudioManager.hpp"
#include "InputManager.hpp"
#include "ConfigManager.hpp"
#include "Logger.hpp"
#include "AssetWatcher.hpp"
#include "assets/AssetPipeline.hpp"

struct Core
{
    /**
     * @brief World instance for managing entities and components.
     */
    std::unique_ptr<ecs::ECSWorld> world;

    /**
     * @brief Resource manager for loading and managing game assets.
     */
    std::unique_ptr<ResourceManager> resources;

    /**
     * @brief Audio manager for playing and managing audio resources.
     */
    std::unique_ptr<AudioManager> audio;

    /**
     * @brief Input manager for handling user input.
     */
    std::unique_ptr<InputManager> input;

    /**
     * @brief Config manager for handling configuration settings.
     */
    std::unique_ptr<ConfigManager> config;

    /**
     * @brief Asset watcher for monitoring and managing game assets.
     */
    std::unique_ptr<AssetWatcher> assetWatcher;

    /**
     * @brief Asset pipeline for processing and managing asset imports.
     */
    std::unique_ptr<AssetPipeline> pipeline;

    /**
     * @brief Default constructor for Core.
     *
     * Initializes the ECS world, resource manager, audio manager, input manager, and config manager.
     */
    Core();

    /**
     * @brief Default destructor for Core.
     *
     * Cleans up the ECS world, resource manager, audio manager, input manager, and config manager.
     */
    ~Core();
};