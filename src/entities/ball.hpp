#ifndef BALL_HPP
#define BALL_HPP

#include "raylib.h"
#include <cmath>
#include <algorithm>



class Ball
{
public:
    Ball();
    Ball(Vector2 pos, float r, float s, Vector2 v, float a, float f, Color c);

    void Move();
    void Draw() const;

    Vector2 position;
    Vector2 velocity;
    float radius;
    float speed;
    float acceleration;
    float friction;
    Color color;
};

#endif
