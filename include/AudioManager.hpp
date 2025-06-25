#pragma once

#include <string>
#include "raylib.h"

class Core; // Forward declaration

/**
 * @class AudioManager
 * @brief Manages loading, playing, stopping, and unloading of audio resources.
 *
 * The AudioManager class provides an interface for handling audio playback,
 * including both sound effects and music tracks. It maintains internal maps
 * for efficient resource management and ensures proper cleanup of loaded audio.
 */
class AudioManager
{
public:
    AudioManager(Core *core);
    ~AudioManager();

    /**
     * @brief Plays a sound from the specified file path.
     *
     * This function plays the sound associated with the given path. If the sound is not
     * already loaded, it will be loaded first.
     *
     * @param path The file system path to the audio file to play.
     */
    void PlaySound(const std::string &path);

    /**
     * @brief Stops a sound that is currently playing.
     *
     * This function stops the sound associated with the given path if it is currently playing.
     *
     * @param path The file system path to the audio file to stop.
     */
    void StopSound(const std::string &path);

    /**
     * @brief Unloads all loaded audio resources.
     *
     * This function clears all loaded sounds and music from memory, ensuring no resources are leaked.
     */
    void UnloadAll();

    /**
     * @brief Plays music from the specified file path.
     *
     * This function plays the music track associated with the given path. If the music is not
     * already loaded, it will be loaded first.
     *
     * @param path The file system path to the music file to play.
     */
    void PlayMusic(const std::string &path);

    /**
     * @brief Stops music that is currently playing.
     *
     * This function stops the music track associated with the given path if it is currently playing.
     *
     * @param path The file system path to the music file to stop.
     */
    void StopMusic(const std::string &path);

private:
    Core *core; ///< Pointer to the Core instance for managing audio
};