#include "PauseScene.hpp"
#include "scene/SceneManager.hpp"
#include "MainMenuScene.hpp"
#include "raylib.h"
#include <iostream>

using namespace game::scenes;

PauseScene::PauseScene()
    : menuItems{"Resume", "Main Menu"}
{
}

void PauseScene::OnEnter()
{
    selectedIndex = 0;
    inputCooldown = 0.5f; // Debounce pentru input
}

void PauseScene::OnExit() {}

void PauseScene::Update(float dt)
{
    if (inputCooldown > 0.0f)
        inputCooldown -= dt;
    else
        HandleInput(dt);
}

void PauseScene::HandleInput(float)
{
    if (IsKeyPressed(KEY_UP))
    {
        selectedIndex = (selectedIndex - 1 + menuItems.size()) % menuItems.size();
        inputCooldown = 0.15f;
    }
    else if (IsKeyPressed(KEY_DOWN))
    {
        selectedIndex = (selectedIndex + 1) % menuItems.size();
        inputCooldown = 0.15f;
    }
    else if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
    {
        ProcessSelection();
        inputCooldown = 0.25f;
    }
    else if (IsKeyPressed(KEY_ESCAPE))
    {
        // Shortcut pentru resume
        if (manager)
        {
            manager->PopScene();
        }
    }
}

void PauseScene::ProcessSelection()
{
    if (!manager)
        return;
    const std::string &item = menuItems[selectedIndex];
    if (item == "Resume")
    {
        manager->PopScene(); // Revino la joc
    }
    else if (item == "Main Menu")
    {
        auto menu = std::make_unique<MainMenuScene>();
        menu->SetSceneManager(manager);
        manager->PopAllAndPush(std::move(menu)); // Înlocuiește GameScene cu MainMenuScene
    }
}

void PauseScene::Draw()
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Overlay semi-transparent
    DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.6f));
    DrawText("PAUSED", screenWidth / 2 - MeasureText("PAUSED", 60) / 2, 120, 60, YELLOW);

    for (size_t i = 0; i < menuItems.size(); ++i)
    {
        Color color = (i == selectedIndex) ? GREEN : GRAY;
        int y = 220 + static_cast<int>(i) * 50;
        DrawText(menuItems[i].c_str(), screenWidth / 2 - MeasureText(menuItems[i].c_str(), 30) / 2, y, 30, color);
    }
}