#include "npc.hpp"
#include "raylib.h"

NPC::NPC(Vector2 startPos, float spd, float tileSz, const std::string &npcName, const std::string &spritePath)
    : Entity(startPos, spd, {tileSz, tileSz}, "npc"),
      name(npcName)
{
    sprite = LoadTexture(spritePath.c_str());
}

void NPC::Update()
{
    // Pentru moment, NPC nu face nimic în update
    Entity::Update();
}

void NPC::Draw() const
{
    DrawTexturePro(
        sprite,
        {0, 0, (float)sprite.width, (float)sprite.height},
        {position.x, position.y, size.x, size.y},
        {0, 0},
        0.0f,
        WHITE);
}

NPC::~NPC()
{
    UnloadTexture(sprite);
}