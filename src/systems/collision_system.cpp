#include "collision_system.hpp"

std::vector<std::pair<const Collider *, const Collider *>> CollisionSystem::DetectCollisions(
    const std::vector<std::shared_ptr<Collider>> &colliders)
{
    std::vector<std::pair<const Collider *, const Collider *>> result;
    for (size_t i = 0; i < colliders.size(); ++i)
    {
        for (size_t j = i + 1; j < colliders.size(); ++j)
        {
            if (CheckCollision(*colliders[i], *colliders[j]))
            {
                result.emplace_back(colliders[i].get(), colliders[j].get());
            }
        }
    }
    return result;
}

bool CollisionSystem::CheckCollision(const Collider &a, const Collider &b)
{
    if (a.type == ColliderType::Rectangle && b.type == ColliderType::Rectangle)
        return RectRect(a.rect, b.rect);
    if (a.type == ColliderType::Circle && b.type == ColliderType::Circle)
        return CircleCircle(a.center, a.radius, b.center, b.radius);
    if (a.type == ColliderType::Rectangle && b.type == ColliderType::Circle)
        return CircleRect(b.center, b.radius, a.rect);
    if (a.type == ColliderType::Circle && b.type == ColliderType::Rectangle)
        return CircleRect(a.center, a.radius, b.rect);
    return false;
}

bool CollisionSystem::RectRect(const Rectangle &r1, const Rectangle &r2)
{
    return !(r1.x + r1.width < r2.x || r2.x + r2.width < r1.x ||
             r1.y + r1.height < r2.y || r2.y + r2.height < r1.y);
}

bool CollisionSystem::CircleCircle(Vector2 c1, float r1, Vector2 c2, float r2)
{
    float dx = c1.x - c2.x;
    float dy = c1.y - c2.y;
    float distSq = dx * dx + dy * dy;
    float radSum = r1 + r2;
    return distSq <= radSum * radSum;
}

bool CollisionSystem::CircleRect(Vector2 center, float radius, const Rectangle &rect)
{
    return CheckCollisionCircleRec(center, radius, rect);
}