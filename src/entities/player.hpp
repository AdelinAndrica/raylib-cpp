#pragma once
#include "entity.hpp"
#include <string>
#include <unordered_map>
#include "raylib.h"

enum class Direction
{
    Up,
    Down,
    Left,
    Right
};

class Player : public Entity
{
public:
    std::string name;
    Texture2D sprite;
    Direction direction;
    bool isMoving;
    Vector2 targetPosition;
    float tileSize;
    std::unordered_map<std::string, int> stats;

    Player(Vector2 startPos, float spd, float tileSz, const std::string &playerName);

    void Update() override;
    void Draw() const override;

    void HandleInput();
    void Move(Direction dir);

    void SetSprite(Texture2D tex);
    void SetStat(const std::string &stat, int value);
    int GetStat(const std::string &stat) const;

    ~Player() override;
};