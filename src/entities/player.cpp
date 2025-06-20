#include "player.hpp"
#include "raylib.h"

Player::Player(Vector2 pos, float spd, Vector2 sz, const std::string &playerName)
    : Entity(pos, spd, sz, "player"), name(playerName)
{
    // Poți încărca sprite-ul aici sau să folosești un resource manager extern
    sprite = LoadTexture("assets/player.png");
}

void Player::HandleInput()
{
    // Exemplu simplu de input WASD/arrow keys, adaptabil după nevoie
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        position.x += speed * GetFrameTime();
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        position.x -= speed * GetFrameTime();
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
        position.y += speed * GetFrameTime();
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
        position.y -= speed * GetFrameTime();

    // Aici poți adăuga logica de deschidere inventar, interacțiune, animații etc.
}

void Player::Update()
{
    HandleInput();
    // Update componente (buff-uri, efecte etc)
    Entity::Update();
    // Alte logici specifice Player-ului pot fi adăugate aici
}

void Player::Draw() const
{
    // Poziționează sprite-ul centrat în funcție de size
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
    // Unload vechiul sprite dacă e cazul!
    UnloadTexture(sprite);
    sprite = tex;
}

void Player::SetName(const std::string &newName)
{
    name = newName;
}

Player::~Player()
{
    UnloadTexture(sprite);
}