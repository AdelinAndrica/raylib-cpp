#include "npc.hpp"
#include "ui/hud.hpp"
#include "core/game_state.hpp"

NPC::NPC(Vector2 pos, float r, Color col, Vector2 vel)
    : position(pos), radius(r), color(col), velocity(vel)
{
}

void NPC::Move()
{
}

void NPC::Draw() const
{
    DrawCircleV(position, radius, color);
}

bool NPC::isPlayerNear()
{
}

void NPC::startConversation()
{
    // This will use HUD
    HUD::ShowMessage(std::string("Hello! I am an NPC. How can I help you?"));
}

void NPC::checkConditions()
{
}