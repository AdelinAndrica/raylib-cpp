#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include "raylib.h"

class InputManager
{
public:
    InputManager() = default;
    ~InputManager() = default;

    // Mapare acțiune -> taste
    void BindKey(const std::string &action, int key);
    void UnbindKey(const std::string &action, int key);
    void ClearBindings(const std::string &action);

    // Query acțiune
    bool IsActionPressed(const std::string &action) const;
    bool IsActionDown(const std::string &action) const;
    bool IsActionReleased(const std::string &action) const;

    // Pentru debug/config
    const std::vector<int> &GetKeysForAction(const std::string &action) const;

private:
    std::unordered_map<std::string, std::vector<int>> bindings;
};