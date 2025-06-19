#pragma once
#include "game_state.hpp"

class HUD
{
public:
    HUD();

    void Draw(const GameState &state) const;

    // Afiseaza mesaj
    static void ShowMessage(const std::string &message);
};