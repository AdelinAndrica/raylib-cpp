#include "gameplay_logic.hpp"

void HandleGameplayLogic(Ball &ball, Level &level, GameState &gameState)
{
    level.Load();

    // Coliziune cu obstacol
    Obstacle *hitObstacle = CollisionSystem::CheckBallObstacleCollision(ball, level.Obstacles);
    if (hitObstacle)
    {
        gameState.lives--;
        if (gameState.lives <= 0)
            gameState.isGameOver = true;
        // Poți adăuga și alte reacții aici (resetare poziție, efecte etc.)
    }

    // Coliziune cu checkpoint
    Checkpoint *hitCheckpoint = CollisionSystem::CheckBallCheckpointCollision(ball, level.Obstacles);
    if (hitCheckpoint)
    {
        gameState.score++;
        hitCheckpoint->Destroy();
    }
}