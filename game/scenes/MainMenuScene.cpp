#include "scene/SceneManager.hpp"
#include "MainMenuScene.hpp"
#include "OptionsScene.hpp" // presupunem că ai o scenă de opțiuni definită
#include "GameScene.hpp"    // presupunem că ai o scenă de joc definită
#include "raylib.h"         // presupunem raylib pentru input & drawing
#include <iostream>
using namespace game::scenes;

MainMenuScene::MainMenuScene()
    : menuItems{"Start Game", "Options", "Exit"} {}

void MainMenuScene::OnEnter()
{
    selectedIndex = 0;
    inputCooldown = 0.25f;
    fadeAlpha = 1.0f; // Start cu fade-in
    fadingIn = true;
}

void MainMenuScene::OnExit()
{
    // Cleanup dacă e nevoie (resurse, sunete, etc.)
}

void MainMenuScene::Update(float dt)
{
    if (fadingIn)
    {
        fadeAlpha -= dt * 2.0f;
        if (fadeAlpha <= 0.0f)
        {
            fadeAlpha = 0.0f;
            fadingIn = false;
        }
    }

    if (inputCooldown > 0.0f)
    {
        inputCooldown -= dt;
    }
    else
    {
        HandleInput(dt);
    }
}

void MainMenuScene::HandleInput(float)
{
    // Navigare sus/jos (keyboard)
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
}

void MainMenuScene::ProcessSelection()
{
    if (!manager)
        return;
    const std::string &item = menuItems[selectedIndex];
    if (item == "Start Game")
    {
        auto gameScene = std::make_unique<game::scenes::GameScene>();
        gameScene->SetSceneManager(manager);
        manager->ReplaceScene(std::move(gameScene));
    }
    else if (item == "Options")
    {
        auto optionsScene = std::make_unique<game::scenes::OptionsScene>();
        optionsScene->SetSceneManager(manager);
        manager->PushScene(std::move(optionsScene));
    }
    else if (item == "Exit")
    {
        // Închide aplicația
        CloseWindow();
        exit(0); // sau manager->PopAllAndPush(std::make_unique<ExitScene>());
    }
}

void MainMenuScene::Draw()
{
    ClearBackground(RAYWHITE);
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Titlu
    DrawText("GAME TITLE", screenWidth / 2 - MeasureText("GAME TITLE", 40) / 2, 100, 40, DARKBLUE);

    // Meniu
    for (size_t i = 0; i < menuItems.size(); ++i)
    {
        Color color = (i == selectedIndex) ? MAROON : DARKGRAY;
        int y = 250 + static_cast<int>(i) * 50;
        DrawText(menuItems[i].c_str(), screenWidth / 2 - MeasureText(menuItems[i].c_str(), 30) / 2, y, 30, color);
    }

    // Fade-in efect
    if (fadeAlpha > 0.0f)
    {
        DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, fadeAlpha));
    }
}