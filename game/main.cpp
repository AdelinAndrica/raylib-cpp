#include "raylib.h"
#include "scene/SceneManager.hpp"
#include "scenes/MainMenuScene.hpp"
#include <memory>

int main()
{
    // Inițializează fereastra
    InitWindow(800, 600, "Test MainMenuScene");
    // Dezactivam exit-ul cu ESC pentru a testa scena
    SetExitKey(0);
    SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT); // Setăm fereastra ca redimensionabilă și activăm VSync
    SetTargetFPS(60);

    // Creează managerul de scene și adaugă scena de meniu
    scene::SceneManager manager;
    //  Creează scena de meniu și setează managerul
    auto mainMenu = std::make_unique<game::scenes::MainMenuScene>();

    mainMenu->SetSceneManager(&manager);
    // Adaugă scena de meniu în manager
    manager.PushScene(std::move(mainMenu));

    // Loop principal
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        // Update scenă activă
        manager.Update(dt);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw scenă activă
        manager.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}