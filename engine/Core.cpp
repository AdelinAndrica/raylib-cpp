#include "Core.hpp"
#include "ResourceManager.hpp"

Core::Core()
{
    world = std::make_unique<ecs::ECSWorld>();
    resources = std::make_unique<ResourceManager>();
}

Core::~Core() = default;