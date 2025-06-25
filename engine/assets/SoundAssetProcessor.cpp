#include "assets/SoundAssetProcessor.hpp"
#include "Logger.hpp"
#include <filesystem>
#include <fstream>
#include <algorithm>

bool SoundAssetProcessor::CanProcess(const std::string &path) const
{
    std::string ext = std::filesystem::path(path).extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    return ext == ".wav" || ext == ".ogg";
}

bool SoundAssetProcessor::Validate(const std::string &path)
{
    // Exemplu: verifică dacă fișierul nu e gol și are header WAV/OGG
    std::ifstream f(path, std::ios::binary);
    if (!f.is_open())
        return false;
    char header[4] = {0};
    f.read(header, 4);
    // WAV: "RIFF"
    if (header[0] == 'R' && header[1] == 'I' && header[2] == 'F' && header[3] == 'F')
        return true;
    // OGG: "OggS"
    if (header[0] == 'O' && header[1] == 'g' && header[2] == 'g' && header[3] == 'S')
        return true;
    return false;
}

void SoundAssetProcessor::Fallback(const std::string &path)
{
    std::filesystem::copy_file("assets/fallback/fallback.wav", path, std::filesystem::copy_options::overwrite_existing);
    LOG_WARN("[AssetPipeline] Fallback sound copied for: " + path);
}

bool SoundAssetProcessor::Process(const std::string &path)
{
    if (!std::filesystem::exists(path))
    {
        LOG_ERROR("[AssetPipeline] Sound not found: " + path);
        Fallback(path);
        return false;
    }
    if (!Validate(path))
    {
        LOG_ERROR("[AssetPipeline] Sound invalid/corrupt: " + path);
        Fallback(path);
        return false;
    }
    LOG_INFO("[AssetPipeline] Processed sound: " + path);
    return true;
}