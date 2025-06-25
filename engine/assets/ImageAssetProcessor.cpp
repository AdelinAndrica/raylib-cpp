#include "assets/ImageAssetProcessor.hpp"
#include "Logger.hpp"
#include <filesystem>
#include <algorithm>
#include <fstream>

bool ImageAssetProcessor::CanProcess(const std::string &path) const
{
    std::string ext = std::filesystem::path(path).extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    return ext == ".png" || ext == ".jpg" || ext == ".jpeg";
}

bool ImageAssetProcessor::Validate(const std::string &path)
{
    // Exemplu: verifică dacă fișierul nu e gol și are header PNG/JPG
    std::ifstream f(path, std::ios::binary);
    if (!f.is_open())
        return false;
    char header[8] = {0};
    f.read(header, 8);
    // PNG: 89 50 4E 47 0D 0A 1A 0A
    if (header[0] == char(0x89) && header[1] == 'P' && header[2] == 'N' && header[3] == 'G')
        return true;
    // JPG: FF D8 FF
    if ((unsigned char)header[0] == 0xFF && (unsigned char)header[1] == 0xD8 && (unsigned char)header[2] == 0xFF)
        return true;
    return false;
}

void ImageAssetProcessor::Fallback(const std::string &path)
{
    // Exemplu: copie fallback.png peste asset corupt
    std::filesystem::copy_file("assets/fallback/fallback.png", path, std::filesystem::copy_options::overwrite_existing);
    LOG_WARN("[AssetPipeline] Fallback image copied for: " + path);
}

bool ImageAssetProcessor::Process(const std::string &path)
{
    if (!std::filesystem::exists(path))
    {
        LOG_ERROR("[AssetPipeline] Image not found: " + path);
        Fallback(path);
        return false;
    }
    if (!Validate(path))
    {
        LOG_ERROR("[AssetPipeline] Image invalid/corrupt: " + path);
        Fallback(path);
        return false;
    }
    LOG_INFO("[AssetPipeline] Processed image: " + path);
    return true;
}