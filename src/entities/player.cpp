#include "player.hpp"
#include "raylib.h"

Player::Player(Vector2 pos, float spd, const std::string &playerName)
    : Entity(pos, spd), name(playerName)
{
    // Poți schimba calea către sprite-ul dorit sau folosi un manager de resurse
    sprite = LoadTexture("assets/player.png");
}

void Player::Update()
{
    // Exemplu simplu de movement (poți adapta pentru grid sau alte reguli JRPG)
    if (IsKeyDown(KEY_RIGHT))
        position.x += speed * GetFrameTime();
    if (IsKeyDown(KEY_LEFT))
        position.x -= speed * GetFrameTime();
    if (IsKeyDown(KEY_DOWN))
        position.y += speed * GetFrameTime();
    if (IsKeyDown(KEY_UP))
        position.y -= speed * GetFrameTime();
}

void Player::Draw() const
{
    DrawTextureV(sprite, position, WHITE);
}

Player::~Player()
{
    UnloadTexture(sprite);
}