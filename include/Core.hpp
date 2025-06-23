#pragma once

#include <memory>
#include "ecs/ECSWorld.hpp"
#include "ResourceManager.hpp"

// Poți adăuga aici și alți manageri pe viitor (ResourceManager, AudioManager etc.)
struct Core
{
    std::unique_ptr<ecs::ECSWorld> world;
    std::unique_ptr<ResourceManager> resources; // <-- adaugă aici

    Core();
    ~Core();

    // Poți adăuga metode de acces sau utilitare aici
};