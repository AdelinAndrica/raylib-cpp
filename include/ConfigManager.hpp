#pragma once

#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>

class ConfigManager
{
public:
    ConfigManager() = default;
    ~ConfigManager() = default;

    void Set(const std::string &key, const std::string &value);
    std::string Get(const std::string &key, const std::string &defaultValue = "") const;

    void SetInt(const std::string &key, int value);
    int GetInt(const std::string &key, int defaultValue = 0) const;

    void SetFloat(const std::string &key, float value);
    float GetFloat(const std::string &key, float defaultValue = 0.0f) const;

    void SetBool(const std::string &key, bool value);
    bool GetBool(const std::string &key, bool defaultValue = false) const;

    bool LoadFromFile(const std::string &filename);
    bool SaveToFile(const std::string &filename) const;

private:
    std::unordered_map<std::string, std::string> data;
};