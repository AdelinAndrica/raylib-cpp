#pragma once

class Entity; // Forward declaration

class Component
{
public:
    virtual void Update(Entity &owner) = 0;
    virtual ~Component() = default;
};