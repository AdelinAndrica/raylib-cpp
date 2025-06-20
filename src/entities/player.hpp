#pragma once
#include "entity.hpp"
#include <string>
#include "raylib.h"

class Player : public Entity
{
public:
    Texture2D sprite;
    std::string name;

    Player(Vector2 pos, float spd, const std::string &playerName);

    void Update() override;
    void Draw() const override;

    ~Player() override;
};