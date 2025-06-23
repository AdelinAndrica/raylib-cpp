#pragma once

#include "scene/IScene.hpp"
#include "Core.hpp"

namespace scene
{
    class BaseScene : public IScene
    {
    public:
        explicit BaseScene(Core *core) : core(core) {}
        virtual ~BaseScene() = default;

    protected:
        Core *core;
    };
}