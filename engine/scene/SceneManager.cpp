#include "scene/SceneManager.hpp"
#include <cassert>

namespace scene
{

    SceneManager::SceneManager() = default;
    SceneManager::~SceneManager() { Clear(); }

    void SceneManager::PushScene(std::unique_ptr<IScene> scene)
    {
        if (!scenes.empty() && scene->BlocksInputBelow())
            scenes.back()->OnExit();
        scenes.push_back(std::move(scene));
        scenes.back()->OnEnter();
    }

    void SceneManager::PopScene()
    {
        assert(!scenes.empty() && "Nu există nicio scenă pe stivă!");
        scenes.back()->OnExit();
        scenes.pop_back();
        if (!scenes.empty() && scenes.back()->BlocksInputBelow())
            scenes.back()->OnEnter();
    }

    void SceneManager::ReplaceScene(std::unique_ptr<IScene> scene)
    {
        if (!scenes.empty())
        {
            scenes.back()->OnExit();
            scenes.pop_back();
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
        int idx = 0;
        for (; idx < static_cast<int>(scenes.size()); ++idx)
        {
            if (!scenes[idx]->IsOverlay())
                break;
        }
        return idx;
    }

} // namespace scene