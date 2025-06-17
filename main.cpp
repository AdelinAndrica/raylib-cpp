#include "raylib.h"

int main()
{
    InitWindow(800, 600, "Salut lume din Raylib!");
    SetTargetFPS(60); // Set the target frames-per-second

    while (!WindowShouldClose())
    { // Detect window close button or ESC key
        BeginDrawing();
        ClearBackground(RAYWHITE); // Clear the background with a white color

        DrawText("Raylib merge!", 300, 280, 20, LIGHTGRAY); // Draw text in the center of the window
        EndDrawing();
    }
    CloseWindow(); // Close the window and OpenGL context
    return 0;      // Exit the program
}

