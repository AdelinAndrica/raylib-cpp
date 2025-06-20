#pragma once
#include <vector>
#include "collider.hpp"

class CollisionSystem
{
public:
    // Returnează lista de perechi care se ciocnesc
    static std::vector<std::pair<const Collider *, const Collider *>> DetectCollisions(
        const std::vector<std::shared_ptr<Collider>> &colliders);

    // Verifică coliziunea între oricare doi collideri
    static bool CheckCollision(const Collider &a, const Collider &b);

    // Helperi pentru tipuri concrete
    static bool RectRect(const Rectangle &, const Rectangle &);
    static bool CircleCircle(Vector2, float, Vector2, float);
    static bool CircleRect(Vector2, float, const Rectangle &);
};