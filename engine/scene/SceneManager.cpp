#include "scene/SceneManager.hpp"
#include <cassert>
#include "Profiler.hpp"
#include "Logger.hpp"

namespace scene
{

    SceneManager::SceneManager() = default;
    SceneManager::~SceneManager() { Clear(); }

    void SceneManager::PushScene(std::unique_ptr<IScene> scene)
    {
        if (!scenes.empty() && scene->BlocksInputBelow())
            scenes.back()->OnExit();
        LOG_INFO("Pushed scene: " + scene->GetName());
        scenes.push_back(std::move(scene));
        scenes.back()->OnEnter();
    }

    void SceneManager::PopScene()
    {
        assert(!scenes.empty() && "Nu există nicio scenă pe stivă!");
        LOG_INFO("Popped scene: " + scenes.back()->GetName());
        scenes.back()->OnExit();
        scenes.pop_back();
        if (!scenes.empty() && scenes.back()->BlocksInputBelow())
            scenes.back()->OnEnter();
    }

    void SceneManager::ReplaceScene(std::unique_ptr<IScene> scene)
    {
        if (!scenes.empty())
        {
            LOG_INFO("Replaced scene: " + scenes.back()->GetName() + " with " + scene->GetName());
            scenes.back()->OnExit();
            scenes.pop_back();
        }
        else
        {
            LOG_INFO("Added scene: " + scene->GetName());
        }
        scenes.push_back(std::move(scene));
        scenes.back()->OnEnter();
    }

    void SceneManager::Clear()
    {
        while (!scenes.empty())
        {
            scenes.back()->OnExit();
            scenes.pop_back();
        }
    }

    IScene *SceneManager::CurrentScene() const
    {
        if (scenes.empty())
            return nullptr;
        return scenes.back().get();
    }

    void SceneManager::Update(float dt)
    {
        PROFILE_SCOPE("SceneManager::Update");
        if (scenes.empty())
            return;
        int firstActive = FindFirstActiveIndex();
        for (size_t i = firstActive; i < scenes.size(); ++i)
            scenes[i]->Update(dt);
    }

    void SceneManager::Draw()
    {
        int firstActive = FindFirstActiveIndex();
        for (size_t i = firstActive; i < scenes.size(); ++i)
            scenes[i]->Draw();
    }

    size_t SceneManager::Size() const
    {
        return scenes.size();
    }

    const std::vector<std::unique_ptr<IScene>> &SceneManager::GetStack() const
    {
        return scenes;
    }

    int SceneManager::FindFirstActiveIndex() const
    {
        // Daca avem mai multe scene care nu sunt overlay-uri, găsim ultima scena solidă (IsOverlay == false).
        int idx = scenes.size() - 1;
        for (; idx >= 0; --idx)
        {
            if (!scenes[idx]->IsOverlay())
                break;
        }
        return idx;
    }

    void SceneManager::PopAllAndPush(std::unique_ptr<IScene> newScene)
    {
        while (!scenes.empty())
            scenes.pop_back();
        scenes.push_back(std::move(newScene));
    }
} // namespace scene