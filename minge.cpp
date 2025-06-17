#include "raylib.h"
#include <memory>

Vector2 ballPosition = {400, 300}; // Initial position of the ball at the center of the window
float ballSpeed = 5.0f;            // Speed of the ball movement

// Clamp function for float values
float Clamp(float value, float min, float max)
{
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

// Methods headers
void spawnRectWCheckpoint();
void handleInput();
void handleDrawing();
bool isBallAtCheckpoint();
bool isGameOver = false; // Global variable to track if the game is over

// Structs
struct CollisionWindow
{
    bool isCollidedLeft;
    bool isCollidedRight;
    bool isCollidedTop;
    bool isCollidedBottom;

    void checkCollisionWithWindow(Vector2 ballPosition, float ballRadius)
    {
        isCollidedLeft = (ballPosition.x - ballRadius < 0);
        isCollidedRight = (ballPosition.x + ballRadius > GetScreenWidth());
        isCollidedTop = (ballPosition.y - ballRadius < 0);
        isCollidedBottom = (ballPosition.y + ballRadius > GetScreenHeight());
    }
} CollisionWindow;

struct HUD
{
    // The score on the HUD
    int score;
    int lives;

    // Constructor to initialize the HUD
    HUD() : score(0), lives(3) {} // Initialize score to 0 and lives to 3

    // Method to draw the HUD
    void draw() const
    {
        // Draw the score and lives on the screen in the top left corner inside a rectangle
        DrawRectangle(0, 0, 200, 60, LIGHTGRAY);     // Draw a light gray rectangle for the HUD background
        DrawRectangleLines(0, 0, 200, 60, DARKGRAY); // Draw a dark gray border around the HUD rectangle

        // Draw the score text
        DrawText(TextFormat("Score: %d", score), 10, 10, 20, BLACK);

        for (int i = 0; i < lives; i++)
        {
            // Draw hearts for lives
            DrawCircle(30 + i * 30, 40, 10, RED);           // Draw a red circle for each life
            DrawCircleLines(30 + i * 30, 40, 10, DARKGRAY); // Draw a dark gray border around the heart
        }
        // Draw instructions for the user
        DrawText("Use arrow keys to move the ball", 10, 30, 20, DARKGRAY);
    }

    // Method to reset the HUD
    void reset()
    {
        score = 0; // Reset the score to 0
        lives = 3; // Reset the lives to 3
    }

} HUD;

struct Checkpoint // This is a circle that will act as a checkpoint for the ball
{
    // The position of the checkpoint
    Vector2 position;
    // The radius of the checkpoint circle
    float radius;
    // The color of the checkpoint circle
    Color color;
    bool isActive = true; // Flag to check if the checkpoint is active

    // Constructor to initialize the checkpoint
    Checkpoint(Vector2 pos, float r, Color c) : position(pos), radius(r), color(c) {}
    // Method to draw the checkpoint circle

    void draw() const
    {
        DrawCircleV(position, radius, color);
    }

    // Method to destroy the checkpoint
    void destroy()
    {
        HUD.score += 1;   // Increase the score on the HUD
        isActive = false; // Set the checkpoint as inactive
    }

    // Method to check if the ball is at the checkpoint
    bool isBallAtCheckpoint(Vector2 ballPosition, float ballRadius)
    {
        // Check if the ball is within the checkpoint circle
        if (CheckCollisionCircles(ballPosition, ballRadius, position, radius))
        {
            if (isActive) // If the checkpoint is active
            {
                this->destroy(); // Destroy the checkpoint
                return true;     // Return true if the ball is at the checkpoint
            }
        }
        return false; // Return false if the ball is not at the checkpoint
    }
};

struct RectangleWCheckpoint // This struct represents a rectangle that will act as an obstacle and will have a checkpoint after it is passed
{
    Vector2 position;
    int width;
    int height;
    Color color;
    std::unique_ptr<Checkpoint> checkpoint; // Smart pointer to a checkpoint that will be created after the rectangle is passed
    RectangleWCheckpoint(Vector2 pos, int w, int h, Color c)
        : position(pos), width(w), height(h), color(c), checkpoint(nullptr) {}

    // Method to draw the rectangle
    void draw() const
    {
        DrawRectangleV(position, {static_cast<float>(width), static_cast<float>(height)}, color);
        if (checkpoint) // If the checkpoint is not null, draw it
        {
            checkpoint->draw();
        }
    }

    // Method to check if the ball is at the rectangle
    bool isBallAtRectangle(Vector2 ballPosition, float ballRadius) const
    {
        // Check if the ball is within the rectangle's bounds
        if (CheckCollisionCircleRec(ballPosition, ballRadius, {position.x, position.y, static_cast<float>(width), static_cast<float>(height)}))
        {
            HUD.lives--; // Decrease the lives on the HUD if the ball is at the rectangle
            if (HUD.lives <= 0)
            {
                isGameOver = true; // Set the game over flag if lives are 0
            }
            return true; // Return true if the ball is at the rectangle
        }
        return false; // Return false if the ball is not at the rectangle
    }

    bool isCheckpointCleared()
    {
        return this->checkpoint->isBallAtCheckpoint(ballPosition, 40); // Check if the ball is at the checkpoint
    }
};

// Global variables
std::unique_ptr<RectangleWCheckpoint> rect = nullptr; // Pointer to a rectangle with a checkpoint. We will have only one rectangle at a time

int main()
{
    InitWindow(800, 600, "Mingea se misca!");
    SetTargetFPS(60); // Set the target frames-per-second

    while (!WindowShouldClose())
    {
        if (isGameOver)
        {
            // If the game is over, display a message
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Game Over! Press R to restart.", 200, 280, 20, RED);
            EndDrawing();
            
            if (IsKeyPressed(KEY_R))
            {
                // Reset the game if R is pressed
                HUD.reset();
                isGameOver = false;
                ballPosition = {400, 300}; // Reset ball position
                rect.reset();              // Reset the rectangle
            }
        }
        else
        {
            handleInput();   // Handle user input for moving the ball
            handleDrawing(); // Handle drawing the ball and instructions
        }

        // The drawRandomRect function is not used in this implementation
        // spawnRectWCheckpoint(); // Uncomment if you want to use it later
    }

    CloseWindow(); // Close the window and OpenGL context
    return 0;      // Exit the program
}

void spawnRectWCheckpoint()
{
    // This function spawns a rectangle with a checkpoint after it is passed
    // Generate random position for the rectangle, ensuring it doesn't overlap with the ball
    int rectWidth = 100;
    int rectHeight = 50;
    Vector2 rectPos;
    do
    {
        rectPos.x = GetRandomValue(0, GetScreenWidth() - rectWidth);
        rectPos.y = GetRandomValue(0, GetScreenHeight() - rectHeight);
    } while (
        rectPos.x < ballPosition.x + 80 && rectPos.x + rectWidth > ballPosition.x - 80 &&
        rectPos.y < ballPosition.y + 80 && rectPos.y + rectHeight > ballPosition.y - 80);

    rect = std::make_unique<RectangleWCheckpoint>(rectPos, rectWidth, rectHeight, BLUE);

    // Place the checkpoint near the rectangle, but not overlapping it
    float checkpointRadius = 20;
    Vector2 checkpointPos;
    int offset = 30 + checkpointRadius; // Distance from rectangle edge

    // Randomly pick a side to place the checkpoint
    int side = GetRandomValue(0, 3);
    switch (side)
    {
    case 0: // Top
        checkpointPos.x = rectPos.x + rectWidth / 2;
        checkpointPos.y = rectPos.y - offset;
        break;
    case 1: // Bottom
        checkpointPos.x = rectPos.x + rectWidth / 2;
        checkpointPos.y = rectPos.y + rectHeight + offset;
        break;
    case 2: // Left
        checkpointPos.x = rectPos.x - offset;
        checkpointPos.y = rectPos.y + rectHeight / 2;
        break;
    case 3: // Right
        checkpointPos.x = rectPos.x + rectWidth + offset;
        checkpointPos.y = rectPos.y + rectHeight / 2;
        break;
    }

    // Clamp checkpoint position to stay inside window
    checkpointPos.x = Clamp(checkpointPos.x, checkpointRadius, GetScreenWidth() - checkpointRadius);
    checkpointPos.y = Clamp(checkpointPos.y, checkpointRadius, GetScreenHeight() - checkpointRadius);

    rect->checkpoint = std::make_unique<Checkpoint>(checkpointPos, checkpointRadius, GREEN);
}

void handleInput()
{
    // INPUT HANDLING
    CollisionWindow.checkCollisionWithWindow(ballPosition, 40); // Check if the ball collides with the window boundaries
    if (IsKeyDown(KEY_RIGHT) && !CollisionWindow.isCollidedRight)
    {
        ballPosition.x += ballSpeed; // Move the ball to the right
    }
    if (IsKeyDown(KEY_LEFT) && !CollisionWindow.isCollidedLeft)
    {
        ballPosition.x -= ballSpeed; // Move the ball to the left
    }
    if (IsKeyDown(KEY_UP) && !CollisionWindow.isCollidedTop)
    {
        ballPosition.y -= ballSpeed; // Move the ball up
    }
    if (IsKeyDown(KEY_DOWN) && !CollisionWindow.isCollidedBottom)
    {
        ballPosition.y += ballSpeed; // Move the ball down
    }
}

void handleDrawing()
{
    // DRAWING
    BeginDrawing();
    ClearBackground(RAYWHITE);                             // Clear the background with a white color
    DrawText("Mingea se misca!", 300, 280, 20, LIGHTGRAY); // Draw text in the center of the window
    DrawCircleV(ballPosition, 40, RED);                    // Draw the ball at its current position
    if (rect)                                              // If the rectangle is not null, draw it
    {
        rect->draw(); // Draw the rectangle and its checkpoint
    }
    else
    {
        spawnRectWCheckpoint(); // Spawn a rectangle with a checkpoint if it doesn't exist
    }
    HUD.draw();   // Draw the HUD with the score
    EndDrawing(); // End the drawing process

    if (rect && (rect->isCheckpointCleared() || rect->isBallAtRectangle(ballPosition, 40)))
    {
        // If the ball has cleared the checkpoint, delete the rectangle
        spawnRectWCheckpoint(); // Spawn a new rectangle with a checkpoint
    }
}