#pragma once
#include "raylib.h"
#include <memory>

enum class ColliderType
{
    Rectangle,
    Circle,
    // Poți adăuga altele dacă vrei (Polygon, Capsule...)
};

struct Collider
{
    ColliderType type;
    int entityId; // sau un pointer către entitatea asociată (dacă folosești ECS)
    // Pentru Rectangle
    Rectangle rect;
    // Pentru Circle
    Vector2 center;
    float radius;

    // Constructori auxiliari
    static Collider RectangleCollider(int entityId, Rectangle rect);
    static Collider CircleCollider(int entityId, Vector2 center, float radius);
};