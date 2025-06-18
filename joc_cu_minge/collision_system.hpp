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

    // Returnează pointer la primul checkpoint activ cu care mingea colizionează, sau nullptr
    static Checkpoint *CheckBallCheckpointCollision(const Ball &ball, const std::vector<std::unique_ptr<Obstacle>> &obstacles);
};