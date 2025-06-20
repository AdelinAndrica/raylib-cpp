#pragma once
#include "entity.hpp"
#include <string>
#include <unordered_map>
#include "raylib.h"

class Map; // Forward declaration

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

    void HandleInput(const Map &map);
    void Move(Direction dir);

    void SetSprite(Texture2D tex);
    void SetStat(const std::string &stat, int value);
    int GetStat(const std::string &stat) const;

    // player.hpp
    int GetCurrentTileX() const override;
    int GetCurrentTileY() const override;
    int GetNextTileX(Direction dir) const;
    int GetNextTileY(Direction dir) const;

    // Events
    void OnTrigger(TileType type, int transitionTarget) override;

    ~Player() override;
};