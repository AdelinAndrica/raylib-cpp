#pragma once
#include "raylib.h"
#include <string>
#include <vector>
#include <memory>

// Forward declaration pentru Component
class Component;

class Entity
{
public:
    Vector2 position;
    float speed;
    Vector2 size;
    bool isActive;
    std::string tag;

    std::vector<std::unique_ptr<Component>> components;

    Entity(Vector2 pos, float spd, Vector2 sz, const std::string &t = "entity");

    void AddComponent(std::unique_ptr<Component> comp);

    // Update pentru entitate și componente
    virtual void Update();

    // Desenare (abstract)
    virtual void Draw() const = 0;

    // Bounding box pentru coliziuni simple (AABB)
    virtual Rectangle GetBoundingBox() const;

    // Interacțiuni (poate fi suprascrisă în clasele derivate)
    virtual void OnInteract(Entity *other);

    // Găsește componenta de un anumit tip (dinamic_cast)
    template <typename T>
    T *GetComponent()
    {
        for (const auto &comp : components)
        {
            if (T *casted = dynamic_cast<T *>(comp.get()))
            {
                return casted;
            }
        }
        return nullptr; // Nu a găsit componenta
    }

    virtual ~Entity();
};