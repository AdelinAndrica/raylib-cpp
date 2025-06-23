#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include "raylib.h"

class ResourceManager
{
public:
    ResourceManager() = default;
    ~ResourceManager();

    Texture2D &LoadTexture(const std::string &path);
    void UnloadAll();

private:
    std::unordered_map<std::string, Texture2D> textures;
};