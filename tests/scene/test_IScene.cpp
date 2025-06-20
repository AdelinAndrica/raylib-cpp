#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <scene/IScene.hpp>
#include <string>
#include <sstream>

// Clasă de test (dummy) care implementează IScene pentru a verifica polimorfismul și corectitudinea contractului
class DummyScene : public scene::IScene
{
public:
    bool entered = false, exited = false, updated = false, drawn = false;
    float last_dt = 0.0f;
    std::stringstream log;

    void OnEnter() override
    {
        entered = true;
        log << "OnEnter;";
    }
    void OnExit() override
    {
        exited = true;
        log << "OnExit;";
    }
    void Update(float dt) override
    {
        updated = true;
        last_dt = dt;
        log << "Update(" << dt << ");";
    }
    void Draw() override
    {
        drawn = true;
        log << "Draw;";
    }
    std::string GetName() const override { return "DummyScene"; }
    bool BlocksInputBelow() const override { return false; }
    bool IsOverlay() const override { return true; }
};

TEST_CASE("IScene contract: polimorfism și funcționalitate minimă", "[scene][IScene]")
{
    DummyScene scene;

    SECTION("OnEnter/OnExit/Update/Draw pot fi apelate și setează starea corect")
    {
        REQUIRE_FALSE(scene.entered);
        scene.OnEnter();
        REQUIRE(scene.entered);

        REQUIRE_FALSE(scene.exited);
        scene.OnExit();
        REQUIRE(scene.exited);

        REQUIRE_FALSE(scene.updated);
        scene.Update(0.25f);
        REQUIRE(scene.updated);
        REQUIRE(scene.last_dt == 0.25f);

        REQUIRE_FALSE(scene.drawn);
        scene.Draw();
        REQUIRE(scene.drawn);
    }

    SECTION("GetName, BlocksInputBelow, IsOverlay pot fi suprascrise")
    {
        REQUIRE(scene.GetName() == "DummyScene");
        REQUIRE(scene.BlocksInputBelow() == false);
        REQUIRE(scene.IsOverlay() == true);
    }

    SECTION("Poate fi folosită polimorfic")
    {
        scene::IScene *pScene = &scene;
        pScene->OnEnter();
        pScene->Update(1.0f);
        pScene->Draw();
        pScene->OnExit();

        REQUIRE(scene.log.str() == "OnEnter;Update(1);Draw;OnExit;");
    }

    SECTION("Implicit: metodele extensibile au implementări default sensibile")
    {
        struct MinimalScene : public scene::IScene
        {
            void OnEnter() override {}
            void OnExit() override {}
            void Update(float) override {}
            void Draw() override {}
        };
        MinimalScene ms;
        REQUIRE(ms.GetName() == "UnnamedScene");
        REQUIRE(ms.BlocksInputBelow() == true);
        REQUIRE(ms.IsOverlay() == false);
    }
}