#pragma once

struct GameState
{
    bool isGameOver;
    Vector2 ballPosition;
    Vector2 ballVelocity;
    Vector2 paddlePosition;
    float paddleWidth;
    float paddleHeight; 
    int score;
    int lives;
    
    GameState() : isGameOver(false) {}
    void Reset() { isGameOver = false; }
};