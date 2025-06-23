#include "OptionsScene.hpp"
#include "scene/SceneManager.hpp"
#include "raylib.h"
#include <iostream>

using namespace game::scenes;


void OptionsScene::OnEnter()
{
    selectedIndex = 0;
    inputCooldown = 0.0f;
}

void OptionsScene::OnExit() {}

void OptionsScene::Update(float dt)
{
    if (inputCooldown > 0.0f)
        inputCooldown -= dt;
    else
        HandleInput(dt);
}

void OptionsScene::HandleInput(float)
{
    if (IsKeyPressed(KEY_UP))
    {
        selectedIndex = (selectedIndex - 1 + options.size()) % options.size();
        inputCooldown = 0.15f;
    }
    else if (IsKeyPressed(KEY_DOWN))
    {
        selectedIndex = (selectedIndex + 1) % options.size();
        inputCooldown = 0.15f;
    }
    else if (IsKeyPressed(KEY_LEFT) && selectedIndex == 0)
    {
        volume = std::max(0.0f, volume - 0.05f);
        SetMasterVolume(volume);
    }
    else if (IsKeyPressed(KEY_RIGHT) && selectedIndex == 0)
    {
        volume = std::min(1.0f, volume + 0.05f);
        SetMasterVolume(volume);
    }
    else if ((IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)))
    {
        ProcessSelection();
        inputCooldown = 0.5f;
    }
    else if (IsKeyPressed(KEY_ESCAPE))
    {
        if (manager)
            manager->PopScene();
    }
}

void OptionsScene::ProcessSelection()
{
    if (!manager)
        return;
    const std::string &item = options[selectedIndex];
    if (item == "Fullscreen")
    {
        _ToggleFullscreen();
    }
    else if (item == "Back")
    {
        manager->PopScene();
    }
}

void OptionsScene::_ToggleFullscreen()
{
    fullscreen = !fullscreen;
    ToggleFullscreen(); // din raylib
}

void OptionsScene::Draw()
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    ClearBackground(RAYWHITE);

    DrawText("OPTIONS", screenWidth / 2 - MeasureText("OPTIONS", 40) / 2, 100, 40, DARKBLUE);

    for (size_t i = 0; i < options.size(); ++i)
    {
        Color color = (i == selectedIndex) ? MAROON : DARKGRAY;
        int y = 220 + static_cast<int>(i) * 50;

        std::string label = options[i];
        if (i == 0)
        {
            label += " : " + std::to_string(int(volume * 100)) + "%";
        }
        else if (i == 1)
        {
            label += fullscreen ? " : On" : " : Off";
        }

        DrawText(label.c_str(), screenWidth / 2 - MeasureText(label.c_str(), 30) / 2, y, 30, color);
    }
}