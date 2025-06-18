#pragma once
#include "ball.hpp"
#include "obstacle.hpp"
#include "checkpoint.hpp"
#include <vector>

class CollisionSystem
{
public:
    // Returnează pointer la primul obstacle cu care mingea colizionează, sau nullptr
    static Obstacle *CheckBallObstacleCollision(const Ball &ball, const std::vector<std::unique_ptr<Obstacle>> &obstacles);

    // Returneaza bool daca mingea s-a lovit de obstacolul respectiv
    static bool CheckSingleBallObstacleCollision(const Ball &ball, const Obstacle &obstacle);

    // Returnează bool dacă mingea colizionează cu checkpoint-ul respectiv
    static bool CheckSingleBallCheckpointCollision(const Ball &ball, const Checkpoint &checkpoint);

    // Verifică dacă mingea colizionează cu un checkpoint și returnează pointer la primul checkpoint activ
    static Checkpoint *CheckBallCheckpointCollision(const Ball &ball, const std::vector<std::unique_ptr<Obstacle>> &obstacles);

    // Verifică dacă mingea colizionează cu marginea ferestrei și oprește mingea la margine
    static void CheckBallWindowCollision(Ball &ball, int windowWidth, int windowHeight);

    // Verifică coliziunea între două dreptunghiuri
    static bool CheckRectangleRectangleCollision(Vector2 rect1Pos, float rect1Width, float rect1Height,
                                                 Vector2 rect2Pos, float rect2Width, float rect2Height);
};