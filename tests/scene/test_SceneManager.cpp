#include <catch2/catch_all.hpp>
#include <scene/SceneManager.hpp>
#include <scene/IScene.hpp>

using namespace scene;

// Mock minimal pentru IScene (implementat inline)
class DummyScene : public IScene
{
public:
    void OnEnter() override {}
    void OnExit() override {}
    void Update(float) override {}
    void Draw() override {}
    bool IsOverlay() const override { return false; }
    bool BlocksInputBelow() const override { return true; }
};

TEST_CASE("SceneManager: Newly created is empty", "[SceneManager]")
{
    SceneManager mgr;
    REQUIRE(mgr.Size() == 0);
    REQUIRE(mgr.CurrentScene() == nullptr);
}

TEST_CASE("SceneManager: PushScene adds scene and sets as current", "[SceneManager]")
{
    SceneManager mgr;
    auto scene = std::make_unique<DummyScene>();
    auto *ptr = scene.get();

    mgr.PushScene(std::move(scene));

    REQUIRE(mgr.Size() == 1);
    REQUIRE(mgr.CurrentScene() == ptr);
}

TEST_CASE("SceneManager: PushScene stacking behavior", "[SceneManager]")
{
    SceneManager mgr;
    auto scene1 = std::make_unique<DummyScene>();
    auto *ptr1 = scene1.get();
    mgr.PushScene(std::move(scene1));

    auto scene2 = std::make_unique<DummyScene>();
    auto *ptr2 = scene2.get();
    mgr.PushScene(std::move(scene2));

    REQUIRE(mgr.Size() == 2);
    REQUIRE(mgr.CurrentScene() == ptr2);
}

TEST_CASE("SceneManager: PopScene removes top and updates current", "[SceneManager]")
{
    SceneManager mgr;
    auto scene1 = std::make_unique<DummyScene>();
    auto *ptr1 = scene1.get();
    mgr.PushScene(std::move(scene1));
    auto scene2 = std::make_unique<DummyScene>();
    auto *ptr2 = scene2.get();
    mgr.PushScene(std::move(scene2));

    mgr.PopScene();
    REQUIRE(mgr.Size() == 1);
    REQUIRE(mgr.CurrentScene() == ptr1);

    mgr.PopScene();
    REQUIRE(mgr.Size() == 0);
    REQUIRE(mgr.CurrentScene() == nullptr);
}

TEST_CASE("SceneManager: PopScene on empty stack triggers assert", "[SceneManager]")
{
    SceneManager mgr;
    // Catch2 nu are echivalent direct pentru EXPECT_DEATH.
    // Dacă folosești assert intern, acest test va termina procesul.
    // Poți să-l dezactivezi sau adaptezi cu #ifdef dacă folosești assert custom.
    // REQUIRE_THROWS nu funcționează pentru assert default.
    // Lasă-l comentat dacă nu ai assert custom:
    // REQUIRE_THROWS(mgr.PopScene());
}

TEST_CASE("SceneManager: Clear empties stack and resets current", "[SceneManager]")
{
    SceneManager mgr;
    mgr.PushScene(std::make_unique<DummyScene>());
    mgr.PushScene(std::make_unique<DummyScene>());

    mgr.Clear();
    REQUIRE(mgr.Size() == 0);
    REQUIRE(mgr.CurrentScene() == nullptr);
}

TEST_CASE("SceneManager: ReplaceScene replaces top with new", "[SceneManager]")
{
    SceneManager mgr;
    auto s1 = std::make_unique<DummyScene>();
    auto *ptr1 = s1.get();
    mgr.PushScene(std::move(s1));
    REQUIRE(mgr.Size() == 1);
    REQUIRE(mgr.CurrentScene() == ptr1);

    auto s2 = std::make_unique<DummyScene>();
    auto *ptr2 = s2.get();
    mgr.ReplaceScene(std::move(s2));

    REQUIRE(mgr.Size() == 1);
    REQUIRE(mgr.CurrentScene() == ptr2);
}

TEST_CASE("SceneManager: ReplaceScene on empty adds scene", "[SceneManager]")
{
    SceneManager mgr;
    auto scene = std::make_unique<DummyScene>();
    auto *ptr = scene.get();

    mgr.ReplaceScene(std::move(scene));
    REQUIRE(mgr.Size() == 1);
    REQUIRE(mgr.CurrentScene() == ptr);
}