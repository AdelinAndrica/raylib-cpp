#pragma once

#include "Core.hpp"
#include "scene/BaseScene.hpp"
#include "ecs/ECSWorld.hpp"
#include <memory>
#include <string>

namespace scene
{
    class SceneManager;
} // Forward declaration pentru SceneManager

namespace game::scenes
{

    class GameScene : public scene::BaseScene
    {
    public:
        explicit GameScene(Core *core)
            : scene::BaseScene(core) {}
        void SetSceneManager(scene::SceneManager *mgr) { manager = mgr; }
        void OnEnter() override;
        void OnExit() override;
        void Update(float dt) override;
        void Draw() override;

        std::string GetName() const override { return "GameScene"; }
        bool BlocksInputBelow() const override { return true; }
        bool IsOverlay() const override { return false; }

        // API pentru testare sau debug
        int GetScore() const { return score; }
        float GetElapsedTime() const { return elapsedTime; }

    private:
        int score = 0;
        float elapsedTime = 0.0f;
        bool paused = false;
        float inputCooldown = 0.0f; // Pentru debounce input
        scene::SceneManager *manager = nullptr;
        // Helpers pentru logica de joc și input
        void HandleInput();
        void ResetGame();
    };

} // namespace game::scenes