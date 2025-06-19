#pragma once

#include "raylib.h"
#include <vector>
#include <memory>
#include <algorithm>

class Obstacle;
class NPC;

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