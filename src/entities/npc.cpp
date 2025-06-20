#include "npc.hpp"
#include "raylib.h"

NPC::NPC(Vector2 pos, float spd, const std::string &npcName)
    : Entity(pos, spd), name(npcName)
{
    // Poți schimba calea către sprite-ul dorit sau folosi un manager de resurse
    sprite = LoadTexture("assets/npc.png");
}

void NPC::Update()
{
    // Logica de mișcare pentru NPC (dacă e cazul)
    // Ex: patrulare, idle, etc. Pentru început poate rămâne goală.
}

void NPC::Draw() const
{
    DrawTextureV(sprite, position, WHITE);
}

NPC::~NPC()
{
    UnloadTexture(sprite);
}