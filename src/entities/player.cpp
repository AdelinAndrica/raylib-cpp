#include "player.hpp"
#include "raylib.h"
#include <cmath>
#include "core/game_state.hpp"
#include "world/map.hpp"

Player::Player(Vector2 startPos, float spd, float tileSz, const std::string &playerName)
    : Entity(startPos, spd, {tileSz, tileSz}, "player"),
      name(playerName),
      direction(Direction::Down),
      isMoving(false),
      tileSize(tileSz),
      targetPosition(startPos)
{
    sprite = LoadTexture("assets/images/player.png");

    stats["HP"] = 100;
    stats["MP"] = 50;
    stats["Attack"] = 10;
    stats["Defense"] = 5;
}

int Player::GetCurrentTileX() const
{
    return static_cast<int>(position.x / tileSize);
}
int Player::GetCurrentTileY() const
{
    return static_cast<int>(position.y / tileSize);
}
int Player::GetNextTileX(Direction dir) const
{
    int tx = GetCurrentTileX();
    if (dir == Direction::Left)
        tx -= 1;
    else if (dir == Direction::Right)
        tx += 1;
    return tx;
}
int Player::GetNextTileY(Direction dir) const
{
    int ty = GetCurrentTileY();
    if (dir == Direction::Up)
        ty -= 1;
    else if (dir == Direction::Down)
        ty += 1;
    return ty;
}

void Player::HandleInput(const Map &map)
{
    if (isMoving)
        return;

    Direction wantedDir;
    bool hasInput = false;

    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
    {
        wantedDir = Direction::Up;
        hasInput = true;
    }
    else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
    {
        wantedDir = Direction::Down;
        hasInput = true;
    }
    else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
    {
        wantedDir = Direction::Left;
        hasInput = true;
    }
    else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
    {
        wantedDir = Direction::Right;
        hasInput = true;
    }

    if (hasInput)
    {
        int nextTileX = GetNextTileX(wantedDir);
        int nextTileY = GetNextTileY(wantedDir);
        if (map.isWalkable(nextTileX, nextTileY))
        {
            Move(wantedDir);
        }
        // altfel: nu se poate muta, rămâne pe loc
    }
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

    targetPosition = nextPos;
    isMoving = true;
}

void Player::Update()
{
    // Integrare cu GameState singleton pentru map
    Map &map = *(GameState::GetInstance().currentMap);

    HandleInput(map);

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

    Entity::Update();
}

void Player::Draw() const
{

    // Pregatire dimensiune sprite
    float frameWidth = (float)sprite.width / 6;

    DrawTexturePro(
        sprite,
        {0, 0, frameWidth, (float)sprite.height},
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