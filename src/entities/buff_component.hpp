#pragma once
#include "component.hpp"
#include "raylib.h"
#include <string>

class BuffComponent : public Component
{
public:
    std::string effectName;
    float duration; // secunde

    BuffComponent(const std::string &name, float dur)
        : effectName(name), duration(dur) {}

    void Update(Entity &owner) override
    {
        if (duration > 0)
        {
            duration -= GetFrameTime();
            // Aici poți aplica efectul (ex: owner.speed *= 2)
        }
        // Dacă durata a expirat, poate marchezi componenta pentru ștergere
    }
};