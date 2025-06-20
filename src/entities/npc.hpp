#pragma once
#include "entity.hpp"
#include <string>
#include "raylib.h"

class NPC : public Entity
{
public:
    std::string name;
    Texture2D sprite;

    NPC(Vector2 startPos, float spd, float tileSz, const std::string &npcName, const std::string &spritePath);

    void Update() override;
    void Draw() const override;

    ~NPC() override;
};