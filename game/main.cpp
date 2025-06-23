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
    SetTargetFPS(60); // Setează FPS-ul țintă
    InitAudioDevice(); // Inițializează dispozitivul audio (dacă este necesar)
    SetExitKey(KEY_NULL); // Dezactivează ieșirea cu ESC pentru a controla manual
    SetMasterVolume(0.5f); // Setează volumul inițial
    
    // Creează instanța Core
    auto core = std::make_unique<Core>();

    // Inițializează managerul de scene
    scene::SceneManager sceneManager;

    // Creează scena principală și injectează Core-ul
    auto mainMenu = std::make_unique<game::scenes::MainMenuScene>(core.get());
    mainMenu->SetSceneManager(&sceneManager);

    sceneManager.PushScene(std::move(mainMenu));

    // Main loop
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        sceneManager.Update(dt);
        BeginDrawing();
        sceneManager.Draw();
        EndDrawing();
    }

    return 0;
}
