#include "entity.hpp"
#include "component.hpp"
#include <stdexcept>

Entity::Entity(Vector2 pos, float spd, Vector2 sz, const std::string &t)
    : position(pos), speed(spd), size(sz), isActive(true), tag(t) {}

void Entity::AddComponent(std::unique_ptr<Component> comp)
{
    components.emplace_back(std::move(comp));
}

void Entity::Update()
{
    for (auto &comp : components)
    {
        comp->Update(*this);
    }
}

Rectangle Entity::GetBoundingBox() const
{
    return {position.x, position.y, size.x, size.y};
}

void Entity::OnInteract(Entity * /*other*/) {}

int Entity::GetCurrentTileX() const
{
    throw std::logic_error("Base Entity::GetCurrentTileX called!");
}

int Entity::GetCurrentTileY() const
{
    throw std::logic_error("Base Entity::GetCurrentTileY called!");
}

void Entity::OnTrigger(TileType type, int transitionTarget) {}

Entity::~Entity() = default;

// Template-ul trebuie implementat în header!