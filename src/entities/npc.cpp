#include "npc.hpp"
#include "ui/hud.hpp"
#include "core/game_state.hpp"

NPC::NPC(Vector2 pos, float r, Color col, Vector2 vel)
    : position(pos), radius(r), color(col), velocity(vel)
{
}

void NPC::Move()
{
    position.x += velocity.x * GetFrameTime();
    position.y += velocity.y * GetFrameTime();

    // Bounce off window edges
    if (position.x - radius < 0 || position.x + radius > GetScreenWidth())
    {
        velocity.x *= -1;
        position.x = std::clamp(position.x, radius, (float)GetScreenWidth() - radius);
    }
    if (position.y - radius < 0 || position.y + radius > GetScreenHeight())
    {
        velocity.y *= -1;
        position.y = std::clamp(position.y, radius, (float)GetScreenHeight() - radius);
    }
}

void NPC::Draw() const
{
    DrawCircleV(position, radius, color);
}

bool NPC::isPlayerNear(const Ball &ball)
{
    float dx = position.x - ball.position.x;
    float dy = position.y - ball.position.y;
    return (dx * dx + dy * dy) < (radius + ball.radius) * (radius + ball.radius);
}

void NPC::startConversation()
{
    // This will use HUD
    HUD::ShowMessage(std::string("Hello! I am an NPC. How can I help you?"));
}

void NPC::checkConditions()
{
    // Check if the player has completed certain conditions
    // For example, if the player has collected a certain number of checkpoints
    // This is just a placeholder for actual game logic
    if (isPlayerNear(*GameState::GetInstance().ball))
    {
        startConversation();
    }
}