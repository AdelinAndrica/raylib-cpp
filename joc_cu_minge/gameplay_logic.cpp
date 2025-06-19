#include "gameplay_logic.hpp"
#include <algorithm>

void HandleGameplayLogic(Level &level, GameState &gameState)
{
    level.Update();
    level.Npc->checkConditions();

    // Coliziune cu obstacol
    Obstacle *hitObstacle = CollisionSystem::CheckBallObstacleCollision(level.Obstacles);
    if (hitObstacle)
    {
        gameState.lives--;
        if (gameState.lives <= 0)
            gameState.isGameOver = true;

        // Caută și elimină obstacolul lovit după adresă
        auto it = std::find_if(
            level.Obstacles.begin(),
            level.Obstacles.end(),
            [hitObstacle](const std::unique_ptr<Obstacle> &ptr)
            { return ptr.get() == hitObstacle; });
        if (it != level.Obstacles.end())
        {
            level.Obstacles.erase(it);
        }
        // Poți adăuga și alte reacții aici (resetare poziție, efecte etc.)
    }

    // Coliziune cu checkpoint
    Checkpoint *hitCheckpoint = CollisionSystem::CheckBallCheckpointCollision(level.Obstacles);
    if (hitCheckpoint)
    {
        gameState.score++;
        hitCheckpoint->Destroy();
    }
}