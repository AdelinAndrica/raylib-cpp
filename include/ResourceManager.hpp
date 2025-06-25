#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include "raylib.h"

/**
 * @class ResourceManager
 * @brief Manages loading, storing, and unloading of game resources such as textures, fonts, sounds, and music.
 */
class ResourceManager
{
public:
    /**
     * @brief Default constructor for ResourceManager.
     *
     * Initializes the resource manager without loading any resources.
     */
    ResourceManager() = default;

    /**
     * @brief Default destructor for ResourceManager.
     *
     * Cleans up all loaded resources.
     */
    ~ResourceManager();

    /**
     * @brief Loads a texture from the specified file path.
     *
     * If the texture is already loaded, it returns the cached version.
     * Otherwise, it loads the texture from disk and caches it.
     *
     * @param path The file system path to the texture file.
     * @return Reference to the loaded Texture2D object.
     */
    Texture2D &LoadTexture(const std::string &path);

    /**
     * @brief Loads a font from the specified file path.
     *
     * If the font is already loaded, it returns the cached version.
     * Otherwise, it loads the font from disk and caches it.
     *
     * @param path The file system path to the font file.
     * @return Reference to the loaded Font object.
     */
    Font &LoadFont(const std::string &path);

    /**
     * @brief Loads a sound from the specified file path.
     *
     * If the sound is already loaded, it returns the cached version.
     * Otherwise, it loads the sound from disk and caches it.
     *
     * @param path The file system path to the sound file.
     * @return Reference to the loaded Sound object.
     */
    Sound &LoadSound(const std::string &path);

    /**
     * @brief Loads music from the specified file path.
     *
     * If the music is already loaded, it returns the cached version.
     * Otherwise, it loads the music from disk and caches it.
     *
     * @param path The file system path to the music file.
     * @return Reference to the loaded Music object.
     */
    Music &LoadMusic(const std::string &path);

    /**
     * @brief Unloads all loaded resources.
     *
     * This function clears all textures, fonts, sounds, and music from memory,
     * ensuring no resources are leaked.
     */
    void UnloadAll();

    /**
     * @brief Reloads a texture from the specified file path.
     *
     * This function is used to reload a texture that has already been loaded,
     * discarding the previous version and loading a new one from disk.
     *
     * @param path The file system path to the texture file.
     * @return true if the texture was reloaded successfully, false otherwise.
     */
    bool ReloadTexture(const std::string &path);

    /**
     * @brief Reloads a font from the specified file path.
     *
     * This function is used to reload a font that has already been loaded,
     * discarding the previous version and loading a new one from disk.
     *
     * @param path The file system path to the font file.
     * @return true if the font was reloaded successfully, false otherwise.
     */
    bool ReloadFont(const std::string &path);

    /**
     * @brief Reloads a sound from the specified file path.
     *
     * This function is used to reload a sound that has already been loaded,
     * discarding the previous version and loading a new one from disk.
     *
     * @param path The file system path to the sound file.
     * @return true if the sound was reloaded successfully, false otherwise.
     */
    bool ReloadSound(const std::string &path);

    /**
     * @brief Reloads music from the specified file path.
     *
     * This function is used to reload a music track that has already been loaded,
     * discarding the previous version and loading a new one from disk.
     *
     * @param path The file system path to the music file.
     * @return true if the music was reloaded successfully, false otherwise.
     */
    bool ReloadMusic(const std::string &path);

private:
    /**
     * @brief A map to store loaded textures by their file path.
     *
     * The key is the file path, and the value is the loaded Texture2D object.
     */
    std::unordered_map<std::string, Texture2D> textures;

    /**
     * @brief A map to store loaded fonts by their file path.
     *
     * The key is the file path, and the value is the loaded Font object.
     */
    std::unordered_map<std::string, Font> fonts;

    /**
     * @brief A map to store loaded sounds by their file path.
     *
     * The key is the file path, and the value is the loaded Sound object.
     */
    std::unordered_map<std::string, Sound> sounds;

    /**
     * @brief A map to store loaded music tracks by their file path.
     *
     * The key is the file path, and the value is the loaded Music object.
     */
    std::unordered_map<std::string, Music> musics;
};