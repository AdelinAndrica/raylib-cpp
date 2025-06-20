#pragma once
#include "entities/obstacle.hpp"
#include "entities/checkpoint.hpp"
#include <vector>
#include "raylib.h"
#include "core/game_state.hpp"

class CollisionSystem
{
public:
    // Returnează pointer la primul obstacle cu care mingea colizionează, sau nullptr
    static Obstacle *CheckBallObstacleCollision(const std::vector<std::unique_ptr<Obstacle>> &obstacles);

    // Returneaza bool daca mingea s-a lovit de obstacolul respectiv
    static bool CheckSingleBallObstacleCollision(const Obstacle &obstacle);

    // Returnează bool dacă mingea colizionează cu checkpoint-ul respectiv
    static bool CheckSingleBallCheckpointCollision(const Checkpoint &checkpoint);

    // Verifică dacă mingea colizionează cu un checkpoint și returnează pointer la primul checkpoint activ
    static Checkpoint *CheckBallCheckpointCollision(const std::vector<std::unique_ptr<Obstacle>> &obstacles);

    // Verifică coliziunea între două dreptunghiuri
    static bool CheckRectangleRectangleCollision(Vector2 rect1Pos, float rect1Width, float rect1Height,
                                                 Vector2 rect2Pos, float rect2Width, float rect2Height);

    // Verifica coliziunea intre window si mingea
    static bool CheckBallWindowCollision();
};