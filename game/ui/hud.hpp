#pragma once
#include "raylib.h"
#include <string>

class GameState; // Forward declaration

class HUD
{
public:
    HUD();

    void Draw(const GameState &state) const;

    // Afiseaza mesaj
    static void ShowMessage(const std::string &message);
};