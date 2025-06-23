#include "GameScene.hpp"
#include "scene/SceneManager.hpp"
#include "PauseScene.hpp"
#include "raylib.h"
#include <iostream>

using namespace game::scenes;


void GameScene::OnEnter() { paused = false; }

void GameScene::OnExit() {}

void GameScene::Update(float dt)
{
    if (paused)
        return;
    HandleInput();
    elapsedTime += dt;
    score = static_cast<int>(elapsedTime * 10.0f);
}

void GameScene::HandleInput()
{
    if (IsKeyPressed(KEY_ESCAPE) && manager)
    {
        paused = !paused; // Toggle pauză
        auto pause = std::make_unique<PauseScene>(core);
        pause->SetSceneManager(manager);
        manager->PushScene(std::move(pause));
    }
}

void GameScene::Draw()
{
    ClearBackground(LIGHTGRAY);
    DrawText("GAMEPLAY", GetScreenWidth() / 2 - MeasureText("GAMEPLAY", 40) / 2, 50, 40, DARKGREEN);
    DrawText(TextFormat("Score: %d", score), 50, 120, 30, MAROON);
    DrawText(TextFormat("Time: %.2fs", elapsedTime), 50, 160, 30, MAROON);
}

void GameScene::ResetGame()
{
    score = 0;
    elapsedTime = 0.0f;
    paused = false;
}