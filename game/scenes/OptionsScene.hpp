#pragma once

#include "scene/IScene.hpp"
#include <string>
#include <vector>

namespace scene
{
    class SceneManager;
}

namespace game::scenes
{

    class OptionsScene : public scene::IScene
    {
    public:
        OptionsScene();

        void SetSceneManager(scene::SceneManager *mgr) { manager = mgr; }

        void OnEnter() override;
        void OnExit() override;
        void Update(float dt) override;
        void Draw() override;

        std::string GetName() const override { return "OptionsScene"; }
        bool BlocksInputBelow() const override { return true; }
        bool IsOverlay() const override { return false; }

    private:
        scene::SceneManager *manager = nullptr;
        std::vector<std::string> options;
        int selectedIndex = 0;
        float inputCooldown = 0.0f;

        float volume = 0.5f; // exemplu: volumul
        bool fullscreen = false;

        void HandleInput(float dt);
        void ProcessSelection();
        void _ToggleFullscreen();
    };

} // namespace game::scenes