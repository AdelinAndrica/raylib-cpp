#include "InputManager.hpp"
#include <algorithm>

void InputManager::BindKey(const std::string &action, int key)
{
    auto &keys = bindings[action];
    if (std::find(keys.begin(), keys.end(), key) == keys.end())
        keys.push_back(key);
}

void InputManager::UnbindKey(const std::string &action, int key)
{
    auto &keys = bindings[action];
    keys.erase(std::remove(keys.begin(), keys.end(), key), keys.end());
}

void InputManager::ClearBindings(const std::string &action)
{
    bindings[action].clear();
}

bool InputManager::IsActionPressed(const std::string &action) const
{
    auto it = bindings.find(action);
    if (it == bindings.end())
        return false;
    for (int key : it->second)
        if (IsKeyPressed(key))
            return true;
    return false;
}

bool InputManager::IsActionDown(const std::string &action) const
{
    auto it = bindings.find(action);
    if (it == bindings.end())
        return false;
    for (int key : it->second)
        if (IsKeyDown(key))
            return true;
    return false;
}

bool InputManager::IsActionReleased(const std::string &action) const
{
    auto it = bindings.find(action);
    if (it == bindings.end())
        return false;
    for (int key : it->second)
        if (IsKeyReleased(key))
            return true;
    return false;
}

const std::vector<int> &InputManager::GetKeysForAction(const std::string &action) const
{
    static const std::vector<int> empty;
    auto it = bindings.find(action);
    return (it != bindings.end()) ? it->second : empty;
}