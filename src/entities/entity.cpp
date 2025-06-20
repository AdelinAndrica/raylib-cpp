#include "entity.hpp"
#include "component.hpp"

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

void Entity::OnInteract(Entity * /*other*/)
{
    // Comportament implicit: nimic
}

Entity::~Entity() = default;

// Template-ul trebuie implementat în header!