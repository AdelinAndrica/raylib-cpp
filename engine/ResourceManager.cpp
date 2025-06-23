#include "ResourceManager.hpp"
#include "raylib.h"

ResourceManager::~ResourceManager()
{
    UnloadAll();
}

Texture2D &ResourceManager::LoadTexture(const std::string &path)
{
    auto it = textures.find(path);
    if (it != textures.end())
        return it->second;

    Texture2D tex = LoadTexture(path.c_str());
    textures[path] = tex;
    return textures[path];
}

void ResourceManager::UnloadAll()
{
    for (auto &[_, tex] : textures)
    {
        UnloadTexture(tex);
    }
    textures.clear();
}