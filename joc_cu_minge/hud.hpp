#pragma once

class HUD
{
public:
    int score;
    int lives;

    HUD();

    void Draw() const;
    void Reset();
};