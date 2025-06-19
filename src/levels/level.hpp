#pragma once

#include "raylib.h"
#include "obstacle.hpp"
#include "npc.hpp"
#include <vector>
#include <memory>

class Level
{
public:
    Level();
    ~Level();

    void Load();
    void Update();
    void Draw();
    void Unload();

    void CheckCompletion();
    std::vector<std::unique_ptr<Obstacle>> Obstacles;
    std::unique_ptr<NPC> Npc;
};