#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <scene/SceneManager.hpp>
#include <string>
#include <sstream>

using namespace scene;

// Dummy scene clasa pentru testare
class DummyScene : public IScene
{
public:
    std::string name;
    mutable std::stringstream log;
    bool overlay = false;
    bool blocksInput = true;

    DummyScene(const std::string &n, bool ov = false, bool block = true)
        : name(n), overlay(ov), blocksInput(block) {}

    void OnEnter() override { log << name << ":OnEnter;"; }
    void OnExit() override { log << name << ":OnExit;"; }
    void Update(float dt) override { log << name << ":Update(" << dt << ");"; }
    void Draw() override { log << name << ":Draw;"; }
    std::string GetName() const override { return name; }
    bool BlocksInputBelow() const override { return blocksInput; }
    bool IsOverlay() const override { return overlay; }
};

TEST_CASE("SceneManager: push/pop/replace/clear și overlay-uri", "[scene][SceneManager]")
{
    SceneManager mgr;

    SECTION("PushScene și starea OnEnter/OnExit")
    {
        auto s1 = std::make_unique<DummyScene>("MainMenu");
        DummyScene *raw1 = s1.get();
        mgr.PushScene(std::move(s1));
        REQUIRE(mgr.Size() == 1);
        REQUIRE(raw1->log.str().find("OnEnter") != std::string::npos);

        auto s2 = std::make_unique<DummyScene>("Gameplay");
        DummyScene *raw2 = s2.get();
        mgr.PushScene(std::move(s2));
        REQUIRE(mgr.Size() == 2);
        REQUIRE(raw2->log.str().find("OnEnter") != std::string::npos);
        REQUIRE(raw1->log.str().find("OnExit") != std::string::npos); // MainMenu primește OnExit (BlocksInputBelow==true)
    }

    SECTION("PopScene reactivează scena precedentă dacă bloca inputul")
    {
        auto s1 = std::make_unique<DummyScene>("MainMenu");
        DummyScene *raw1 = s1.get();
        auto s2 = std::make_unique<DummyScene>("Gameplay");
        DummyScene *raw2 = s2.get();
        mgr.PushScene(std::move(s1));
        mgr.PushScene(std::move(s2));
        mgr.PopScene();
        REQUIRE(mgr.Size() == 1);
        REQUIRE(raw2->log.str().find("OnExit") != std::string::npos);
        REQUIRE(raw1->log.str().find("OnEnter") != std::string::npos); // MainMenu primește din nou OnEnter
    }

    SECTION("ReplaceScene curăță corect și apelează OnExit/OnEnter")
    {
        auto s1 = std::make_shared<DummyScene>("MainMenu");
        mgr.PushScene(std::unique_ptr<IScene>(s1.get()));
        auto s2 = std::make_unique<DummyScene>("Gameplay");
        DummyScene *raw2 = s2.get();
        mgr.ReplaceScene(std::move(s2));
        REQUIRE(mgr.Size() == 1);
        // s1 încă trăiește prin shared_ptr, deci poți accesa logul corect:
        REQUIRE(s1->log.str().find("OnExit") != std::string::npos);
        REQUIRE(raw2->log.str().find("OnEnter") != std::string::npos);
    }

    SECTION("Clear golește stiva și apelează OnExit pentru fiecare")
    {
        // Folosește shared_ptr pentru a păstra accesul la DummyScene după Clear
        auto s1 = std::make_shared<DummyScene>("A");
        auto s2 = std::make_shared<DummyScene>("B");
        auto s3 = std::make_shared<DummyScene>("C");

        mgr.PushScene(std::unique_ptr<IScene>(s1.get()));
        mgr.PushScene(std::unique_ptr<IScene>(s2.get()));
        mgr.PushScene(std::unique_ptr<IScene>(s3.get()));

        mgr.Clear();

        REQUIRE(mgr.Size() == 0);
        REQUIRE(s1->log.str().find("OnExit") != std::string::npos);
        REQUIRE(s2->log.str().find("OnExit") != std::string::npos);
        REQUIRE(s3->log.str().find("OnExit") != std::string::npos);
    }

    SECTION("Overlay-urile nu blochează inputul și nu scot din OnExit scena de dedesubt")
    {
        auto s1 = std::make_unique<DummyScene>("Gameplay", false, true);
        DummyScene *raw1 = s1.get();
        auto overlay = std::make_unique<DummyScene>("Dialog", true, false);
        DummyScene *raw2 = overlay.get();
        mgr.PushScene(std::move(s1));
        mgr.PushScene(std::move(overlay));
        // Gameplay nu primește OnExit, pentru că overlay-ul nu blochează inputul
        REQUIRE(raw1->log.str().find("OnExit") == std::string::npos);
        REQUIRE(raw2->log.str().find("OnEnter") != std::string::npos);
    }

    SECTION("Update/Draw procesează doar scenele relevante (overlay logic)")
    {
        // S1 - solid, S2 - overlay, S3 - overlay
        auto s1 = std::make_unique<DummyScene>("Gameplay", false, true);
        auto s2 = std::make_unique<DummyScene>("HUD", true, false);
        auto s3 = std::make_unique<DummyScene>("Dialog", true, false);
        DummyScene *raw1 = s1.get();
        DummyScene *raw2 = s2.get();
        DummyScene *raw3 = s3.get();

        mgr.PushScene(std::move(s1));
        mgr.PushScene(std::move(s2));
        mgr.PushScene(std::move(s3));

        mgr.Update(0.5f);
        mgr.Draw();

        // Doar Gameplay, HUD și Dialog trebuie să fi primit Update/Draw (din FindFirstActiveIndex).
        REQUIRE(raw1->log.str().find("Update") != std::string::npos);
        REQUIRE(raw2->log.str().find("Update") != std::string::npos);
        REQUIRE(raw3->log.str().find("Update") != std::string::npos);

        REQUIRE(raw1->log.str().find("Draw") != std::string::npos);
        REQUIRE(raw2->log.str().find("Draw") != std::string::npos);
        REQUIRE(raw3->log.str().find("Draw") != std::string::npos);
    }
}