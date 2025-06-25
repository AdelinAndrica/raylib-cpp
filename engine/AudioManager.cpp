#include "AudioManager.hpp"
#include "Core.hpp"
#include <iostream>
#include "Logger.hpp"

AudioManager::AudioManager(Core *core_) : core(core_) {}
AudioManager::~AudioManager() = default;

void AudioManager::PlaySound(const std::string &path)
{
    try {
        Sound &s = core->resources->LoadSound(path);
        ::PlaySound(s);
        LOG_INFO("Played sound: " + path);
    } catch (...) {
        LOG_ERROR("Failed to play sound: " + path);
    }
}

void AudioManager::StopSound(const std::string &path)
{
    try {
        Sound &s = core->resources->LoadSound(path);
        ::StopSound(s);
        LOG_INFO("Stopped sound: " + path);
    } catch (...) {
        LOG_ERROR("Failed to stop sound: " + path);
    }
}

void AudioManager::PlayMusic(const std::string &path)
{
    try {
        Music &m = core->resources->LoadMusic(path);
        ::PlayMusicStream(m);
        LOG_INFO("Played music: " + path);
    } catch (...) {
        LOG_ERROR("Failed to play music: " + path);
    }
}

void AudioManager::StopMusic(const std::string &path)
{
    try {
        Music &m = core->resources->LoadMusic(path);
        ::StopMusicStream(m);
        LOG_INFO("Stopped music: " + path);
    } catch (...) {
        LOG_ERROR("Failed to stop music: " + path);
    }
}

void AudioManager::UnloadAll()
{
    // Cleanup is handled by ResourceManager
}