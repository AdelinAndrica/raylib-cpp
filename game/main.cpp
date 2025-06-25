// game/main.cpp
#include "raylib.h"
#include "Core.hpp"
#include "ecs/ECSWorld.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "systems/MovementSystem.hpp"
#include "systems/LoggerSystem.hpp"
#include "systems/TestEmitterSystem.hpp"
#include "scenes/MainMenuScene.hpp"
#include "scene/SceneManager.hpp"
#include <iostream>
#include <memory>

int main()
{
    // Inițializează engine-ul (Core)
    InitWindow(800, 600, "Raylib ECS Game");
    SetTargetFPS(60);      // Setează FPS-ul țintă
    InitAudioDevice();     // Inițializează dispozitivul audio (dacă este necesar)
    SetExitKey(KEY_NULL);  // Dezactivează ieșirea cu ESC pentru a controla manual
    SetMasterVolume(0.5f); // Setează volumul inițial

    // Creează instanța Core
    auto core = std::make_unique<Core>();

    // Inițializează managerul de scene
    scene::SceneManager sceneManager;

    // Creează scena principală și injectează Core-ul
    auto mainMenu = std::make_unique<game::scenes::MainMenuScene>(core.get());
    mainMenu->SetSceneManager(&sceneManager);

    sceneManager.PushScene(std::move(mainMenu));

    bool played = false; // pentru a nu reporni sunetul la fiecare frame

    // Bind acțiuni la taste
    core->input->BindKey("jump", KEY_SPACE);
    core->input->BindKey("pause", KEY_ESCAPE);

    // ConfigManager: salvare/încărcare config
    core->config->SetInt("volume", 80);
    core->config->SaveToFile("config.ini");
    core->config->LoadFromFile("config.ini");
    int vol = core->config->GetInt("volume", 100);

    // LOGGING TEST
    LOG_INFO("Test log info");
    LOG_DEBUG("Test log debug");
    LOG_WARN("Test log warn");
    LOG_ERROR("Test log error");

    // Main loop
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        sceneManager.Update(dt);

        // TEST PlaySound: apasă SPACE pentru a reda efectul sonor o singură dată
        if (IsKeyPressed(KEY_SPACE) && !played)
        {
            LOG_INFO("[Main] Playing sound effect");
            core->audio->PlaySound("assets/audio/main-soundtrack.wav");
            played = true;
        }

        // Query input
        if (core->input->IsActionPressed("jump"))
        {
            // Sari!
        }

        BeginDrawing();
        sceneManager.Draw();
        EndDrawing();
    }

    return 0;
}
