#pragma once
#include "entity.hpp"
#include <string>
#include "raylib.h"

class Player : public Entity
{
public:
    std::string name;
    Texture2D sprite;

    Player(Vector2 pos, float spd, Vector2 sz, const std::string &playerName);

    void Update() override;
    void Draw() const override;

    // Exemplu: funcții suplimentare posibile
    void HandleInput();
    void SetSprite(Texture2D tex);
    void SetName(const std::string &newName);

    ~Player() override;
};