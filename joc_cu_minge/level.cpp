#include "level.hpp"
#include "raylib.h"
#include "collision_system.hpp"
#include <algorithm>

Level::Level()
{
    // Initialize level properties here
}

Level::~Level()
{
}

void Level::Load()
{
    Obstacles.clear();

    // Pozitia initiala a mingii (de exemplu)
    Vector2 ballStartPos = {400, 300};
    float ballRadius = 40.0f;

    // Functie utila pentru verificarea coliziunii cu mingea
    auto overlapsBall = [&](Vector2 pos, float width, float height)
    {
        float closestX = std::max(pos.x, std::min(ballStartPos.x, pos.x + width));
        float closestY = std::max(pos.y, std::min(ballStartPos.y, pos.y + height));
        float dx = ballStartPos.x - closestX;
        float dy = ballStartPos.y - closestY;
        return (dx * dx + dy * dy) < (ballRadius * ballRadius);
    };

    // Exemplu: Spawnează 3 obstacole cu checkpoint-uri, evitând mingea
    struct ObstacleData
    {
        Vector2 pos;
        float w, h;
        Color color;
        Vector2 checkpointPos;
    };

    // Randomize number and properties of obstacles
    const int numObstacles = GetRandomValue(2, 5);
    std::vector<ObstacleData> data;
    for (int i = 0; i < numObstacles; ++i)
    {
        float x = GetRandomValue(100, 700);
        float y = GetRandomValue(100, 500);
        float w = GetRandomValue(60, 140);
        float h = GetRandomValue(30, 70);
        Color color = (i % 3 == 0) ? BLUE : (i % 3 == 1) ? DARKBLUE
                                                         : SKYBLUE;
        Vector2 checkpointPos = {x + GetRandomValue(-30, 30), y - GetRandomValue(40, 80)};
        data.push_back({{x, y}, w, h, color, checkpointPos});
    }

    // Helper lambda to check overlap between two rectangles using CollisionSystem
    auto rectsOverlap = [](Vector2 aPos, float aW, float aH, Vector2 bPos, float bW, float bH)
    {
        return CollisionSystem::CheckRectangleRectangleCollision(aPos, aW, aH, bPos, bW, bH);
    };

    for (const auto &d : data)
    {
        if (overlapsBall(d.pos, d.w, d.h))
            continue;

        bool overlapsOther = false;
        for (const auto &obs : Obstacles)
        {
            if (rectsOverlap(d.pos, d.w, d.h, obs->position, obs->width, obs->height))
            {
                overlapsOther = true;
                break;
            }
        }
        if (!overlapsOther)
        {
            auto obs = std::make_unique<Obstacle>(d.pos, d.w, d.h, d.color);
            obs->checkpoint = std::make_unique<Checkpoint>(d.checkpointPos, 20, GREEN);
            Obstacles.push_back(std::move(obs));
        }
    }
}

void Level::Draw()
{
    for (const auto &obs : Obstacles)
        obs->Draw();
}

void Level::Update()
{
    // Update level logic here
    for (auto &obs : Obstacles)
    {
        if (obs->isCompleted())
        {
            // remove completed obstacles from the level
            this->Obstacles.erase(
                std::remove_if(this->Obstacles.begin(), this->Obstacles.end(),
                               [&obs](const std::unique_ptr<Obstacle> &o)
                               { return o.get() == obs.get(); }),
                this->Obstacles.end());
        }
    }

    // Check if the level is completed
    CheckCompletion();
}

void Level::CheckCompletion()
{
    // Check if all obstacles are cleared or if the level is completed
    // We check the list of obstacles as they get eliminated on completion
    if (Obstacles.empty())
    {
        // We respawn the level with new obstacles
        Load();
    }
}