#include "ConfigManager.hpp"
#include "Logger.hpp"

void ConfigManager::Set(const std::string &key, const std::string &value)
{
    data[key] = value;
    LOG_INFO("Config set: " + key + " = " + value);
}

std::string ConfigManager::Get(const std::string &key, const std::string &defaultValue) const
{
    auto it = data.find(key);
    if (it != data.end())
    {
        LOG_INFO("Config get: " + key + " = " + it->second);
        return it->second;
    }
    LOG_WARN("Config get: " + key + " not found, returning default: " + defaultValue);
    return defaultValue;
}

void ConfigManager::SetInt(const std::string &key, int value)
{
    data[key] = std::to_string(value);
    LOG_INFO("Config set int: " + key + " = " + std::to_string(value));
}

int ConfigManager::GetInt(const std::string &key, int defaultValue) const
{
    auto it = data.find(key);
    if (it != data.end())
    {
        try
        {
            int val = std::stoi(it->second);
            LOG_INFO("Config get int: " + key + " = " + it->second);
            return val;
        }
        catch (const std::exception &e)
        {
            LOG_ERROR("Config get int: failed to convert value for key " + key + ": " + it->second);
        }
    }
    else
    {
        LOG_WARN("Config get int: " + key + " not found, returning default: " + std::to_string(defaultValue));
    }
    return defaultValue;
}

void ConfigManager::SetFloat(const std::string &key, float value)
{
    data[key] = std::to_string(value);
    LOG_INFO("Config set float: " + key + " = " + std::to_string(value));
}

float ConfigManager::GetFloat(const std::string &key, float defaultValue) const
{
    auto it = data.find(key);
    if (it != data.end())
    {
        try
        {
            float val = std::stof(it->second);
            LOG_INFO("Config get float: " + key + " = " + it->second);
            return val;
        }
        catch (const std::exception &e)
        {
            LOG_ERROR("Config get float: failed to convert value for key " + key + ": " + it->second);
        }
    }
    else
    {
        LOG_WARN("Config get float: " + key + " not found, returning default: " + std::to_string(defaultValue));
    }
    return defaultValue;
}

void ConfigManager::SetBool(const std::string &key, bool value)
{
    data[key] = value ? "true" : "false";
    LOG_INFO("Config set bool: " + key + " = " + (value ? "true" : "false"));
}

bool ConfigManager::GetBool(const std::string &key, bool defaultValue) const
{
    auto it = data.find(key);
    if (it != data.end())
    {
        LOG_INFO("Config get bool: " + key + " = " + it->second);
        return it->second == "true";
    }
    LOG_WARN("Config get bool: " + key + " not found, returning default: " + std::string(defaultValue ? "true" : "false"));
    return defaultValue;
}

bool ConfigManager::LoadFromFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        LOG_ERROR("Failed to open config file for reading: " + filename);
        return false;
    }
    std::string line;
    int count = 0;
    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;
        auto eq = line.find('=');
        if (eq == std::string::npos)
            continue;
        std::string key = line.substr(0, eq);
        std::string value = line.substr(eq + 1);
        data[key] = value;
        count++;
        LOG_INFO("Loaded config: " + key + " = " + value);
    }
    LOG_INFO("Loaded " + std::to_string(count) + " config entries from file: " + filename);
    return true;
}

bool ConfigManager::SaveToFile(const std::string &filename) const
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        LOG_ERROR("Failed to open config file for writing: " + filename);
        return false;
    }
    int count = 0;
    for (const auto &[key, value] : data)
    {
        file << key << "=" << value << "\n";
        count++;
    }
    LOG_INFO("Saved " + std::to_string(count) + " config entries to file: " + filename);
    return true;
}