#include "player.hpp"
#include "raylib.h"
#include <cmath>

Player::Player(Vector2 startPos, float spd, float tileSz, const std::string &playerName)
    : Entity(startPos, spd, {tileSz, tileSz}, "player"),
      name(playerName),
      direction(Direction::Down),
      isMoving(false),
      tileSize(tileSz),
      targetPosition(startPos)
{
    sprite = LoadTexture("assets/player.png"); // adaptează calea la nevoie

    // Inițializează stats de bază
    stats["HP"] = 100;
    stats["MP"] = 50;
    stats["Attack"] = 10;
    stats["Defense"] = 5;
}

void Player::HandleInput()
{
    if (isMoving)
        return; // Nu acceptă input până nu ajunge pe tile

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
        Move(Direction::Up);
    else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
        Move(Direction::Down);
    else if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
        Move(Direction::Left);
    else if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
        Move(Direction::Right);
}

void Player::Move(Direction dir)
{
    direction = dir;
    Vector2 nextPos = position;

    switch (dir)
    {
    case Direction::Up:
        nextPos.y -= tileSize;
        break;
    case Direction::Down:
        nextPos.y += tileSize;
        break;
    case Direction::Left:
        nextPos.x -= tileSize;
        break;
    case Direction::Right:
        nextPos.x += tileSize;
        break;
    }

    // TODO: verificare coliziuni/map bounds aici!

    targetPosition = nextPos;
    isMoving = true;
}

void Player::Update()
{
    HandleInput();

    if (isMoving)
    {
        Vector2 delta = {targetPosition.x - position.x, targetPosition.y - position.y};
        float dist = sqrtf(delta.x * delta.x + delta.y * delta.y);
        float moveDist = speed * GetFrameTime();

        if (moveDist >= dist)
        {
            position = targetPosition;
            isMoving = false;
        }
        else
        {
            position.x += moveDist * (delta.x / dist);
            position.y += moveDist * (delta.y / dist);
        }
    }

    Entity::Update(); // update pentru componente/buff-uri
}

void Player::Draw() const
{
    DrawTexturePro(
        sprite,
        {0, 0, (float)sprite.width, (float)sprite.height},
        {position.x, position.y, size.x, size.y},
        {0, 0},
        0.0f,
        WHITE);
}

void Player::SetSprite(Texture2D tex)
{
    UnloadTexture(sprite);
    sprite = tex;
}

void Player::SetStat(const std::string &stat, int value)
{
    stats[stat] = value;
}

int Player::GetStat(const std::string &stat) const
{
    auto it = stats.find(stat);
    return it != stats.end() ? it->second : 0;
}

Player::~Player()
{
    UnloadTexture(sprite);
}