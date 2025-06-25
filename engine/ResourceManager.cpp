#include "ResourceManager.hpp"
#include "raylib.h"
#include "Logger.hpp"
#include "Profiler.hpp"

ResourceManager::~ResourceManager()
{
    UnloadAll();
}

Texture2D &ResourceManager::LoadTexture(const std::string &path)
{
    PROFILE_SCOPE("ResourceManager::LoadTexture");
    auto it = textures.find(path);
    if (it != textures.end())
        return it->second;

    Texture2D tex = LoadTexture(path.c_str());
    if (tex.id == 0)
    {
        LOG_ERROR("Failed to load texture: " + path);
    }
    else
    {
        LOG_INFO("Loaded texture: " + path);
    }
    textures[path] = tex;
    return textures[path];
}

Font &ResourceManager::LoadFont(const std::string &path)
{
    auto it = fonts.find(path);
    if (it != fonts.end())
        return it->second;

    Font font = LoadFont(path.c_str());
    if (font.baseSize == 0)
    {
        LOG_ERROR("Failed to load font: " + path);
    }
    else
    {
        LOG_INFO("Loaded font: " + path);
    }
    fonts[path] = font;
    return fonts[path];
}

Sound &ResourceManager::LoadSound(const std::string &path)
{
    auto it = sounds.find(path);
    if (it != sounds.end())
        return it->second;

    Sound sound = ::LoadSound(path.c_str());
    if (sound.stream.buffer == nullptr)
    {
        LOG_ERROR("Failed to load sound: " + path);
    }
    else
    {
        LOG_INFO("Loaded sound: " + path);
    }
    sounds[path] = sound;
    return sounds[path];
}

Music &ResourceManager::LoadMusic(const std::string &path)
{
    auto it = musics.find(path);
    if (it != musics.end())
        return it->second;

    Music music = LoadMusicStream(path.c_str());
    if (music.stream.buffer == nullptr)
    {
        LOG_ERROR("Failed to load music: " + path);
    }
    else
    {
        LOG_INFO("Loaded music: " + path);
    }
    musics[path] = music;
    return musics[path];
}

void ResourceManager::UnloadAll()
{
    for (auto &[_, tex] : textures)
        UnloadTexture(tex);
    textures.clear();

    for (auto &[_, font] : fonts)
        UnloadFont(font);
    fonts.clear();

    for (auto &[_, sound] : sounds)
        UnloadSound(sound);
    sounds.clear();

    for (auto &[_, music] : musics)
        UnloadMusicStream(music);
    musics.clear();
}

bool ResourceManager::ReloadTexture(const std::string &path)
{
    auto it = textures.find(path);
    if (it != textures.end())
    {
        UnloadTexture(it->second);
        textures.erase(it);
    }
    LoadTexture(path);
    LOG_INFO("Reloaded texture: " + path);
    return true;
}

bool ResourceManager::ReloadFont(const std::string &path)
{
    auto it = fonts.find(path);
    if (it != fonts.end())
    {
        UnloadFont(it->second);
        fonts.erase(it);
    }
    LoadFont(path);
    LOG_INFO("Reloaded font: " + path);
    return true;
}

bool ResourceManager::ReloadSound(const std::string &path)
{
    auto it = sounds.find(path);
    if (it != sounds.end())
    {
        UnloadSound(it->second);
        sounds.erase(it);
    }
    LoadSound(path);
    LOG_INFO("Reloaded sound: " + path);
    return true;
}

bool ResourceManager::ReloadMusic(const std::string &path)
{
    auto it = musics.find(path);
    if (it != musics.end())
    {
        UnloadMusicStream(it->second);
        musics.erase(it);
    }
    LoadMusic(path);
    LOG_INFO("Reloaded music: " + path);
    return true;
}