#pragma once

#include "scene/IScene.hpp"
#include <vector>
#include <string>
#include <functional>
#include <memory>

namespace scene
{
    class SceneManager;
} // Forward declaration pentru SceneManager

namespace game::scenes
{

    class MainMenuScene : public scene::IScene
    {
    public:
        MainMenuScene();

        void SetSceneManager(scene::SceneManager *mgr) { manager = mgr; }

        // Ciclu de viață
        void OnEnter() override;
        void OnExit() override;
        void Update(float dt) override;
        void Draw() override;

        // Identificare & comportament stack
        std::string GetName() const override { return "MainMenu"; }
        bool BlocksInputBelow() const override { return true; }
        bool IsOverlay() const override { return false; }

        // API public: pentru test/mock sau integrare
        int GetSelectedIndex() const { return selectedIndex; }
        const std::vector<std::string> &GetMenuItems() const { return menuItems; }

    private:
        std::vector<std::string> menuItems;
        int selectedIndex = 0;
        float inputCooldown = 0.25f; // Pentru debounce tastatură
        float fadeAlpha = 0.0f;
        bool fadingIn = true;
        scene::SceneManager *manager = nullptr; // Referință la managerul de scene (poate fi setat extern) Dependency Injection

        // Helpers
        void HandleInput(float dt);
        void ProcessSelection();

        // Pentru test sau extensie: callback la selectare (poate fi injectat)
        std::function<void(int)> onSelect;
    };

} // namespace game::scenes