#pragma once

#include "scene/BaseScene.hpp"
#include <string>
#include <vector>

namespace scene
{
    class SceneManager;
}

namespace game::scenes
{

    class PauseScene : public scene::BaseScene
    {
    public:
        PauseScene(Core *core)
            : scene::BaseScene(core)
        {
            // Inițializare opțiuni
            menuItems = {"Resume", "Options", "Exit"};
        }

        void SetSceneManager(scene::SceneManager *mgr) { manager = mgr; }

        void OnEnter() override;
        void OnExit() override;
        void Update(float dt) override;
        void Draw() override;

        std::string GetName() const override { return "PauseScene"; }
        bool BlocksInputBelow() const override { return true; }
        bool IsOverlay() const override { return true; } // Overlay peste GameScene

    private:
        scene::SceneManager *manager = nullptr;
        int selectedIndex = 0;
        float inputCooldown = 0.0f;
        std::vector<std::string> menuItems;

        void HandleInput(float dt);
        void ProcessSelection();
    };

} // namespace game::scenes