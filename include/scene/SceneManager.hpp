#pragma once
#include <memory>
#include <vector>
#include "scene/IScene.hpp"

namespace scene
{

    /**
     * @class SceneManager
     * @brief Manager de scene pentru jocuri și aplicații interactive, folosind o stivă (stack) de scene.
     *
     * SceneManager implementează un pattern de tip "state stack", permițând gestionarea flexibilă a fluxului de joc prin push/pop/replace de scene.
     * Fiecare scenă este derivată din interfața IScene și poate reprezenta o stare distinctă (ex: meniu principal, gameplay, dialog, ecran de pauză, HUD etc.).
     *
     * ### Funcționalități principale:
     * - **PushScene:** Adaugă o scenă nouă peste cea curentă, invocând automat ciclul de viață OnExit/OnEnter unde este cazul.
     * - **PopScene:** Scoate scena de pe vârf și reactivează scena precedentă (OnEnter), dacă aceasta bloca inputul.
     * - **ReplaceScene:** Înlocuiește scena de pe vârf cu una nouă, garantând curățarea și inițializarea corectă.
     * - **Clear:** Șterge complet toate scenele din stivă, invocând OnExit pentru fiecare.
     * - **Update/Draw:** Actualizează și desenează doar scenele relevante (overlay sau solid, de la bază la vârf), pentru suport nativ de HUD, dialoguri, meniuri pop-up etc.
     * - **BlocksInputBelow/IsOverlay:** Respectă contractul scenelor pentru a permite propagarea inputului și desenul corect al overlay-urilor.
     * - **Ownership sigur:** Utilizează exclusiv std::unique_ptr pentru a garanta siguranța memoriei și a resurselor.
     *
     * ### Pattern-uri și scenarii susținute:
     * - **Meniuri nestate:** Meniul principal poate fi înlocuit cu gameplay, iar un dialog sau un HUD poate fi "pushed" peste gameplay.
     * - **Tranziții animate:** Se poate implementa ușor o scenă de tranziție ca overlay peste vechea și noua scenă.
     * - **Debugging și introspecție:** Poți inspecta oricând stiva de scene pentru a vizualiza flow-ul aplicației.
     * - **Restart sau schimbare hard de stare:** Cu metoda Clear poți reseta complet stiva (ex: la game over sau la reload rapid).
     *
     * ### Utilizare tipică:
     * @code
     * scene::SceneManager manager;
     * manager.PushScene(std::make_unique<MainMenuScene>());
     * // ...
     * manager.Update(dt);
     * manager.Draw();
     * // ...
     * manager.ReplaceScene(std::make_unique<GameplayScene>());
     * // ...
     * manager.PopScene(); // Revine la meniu sau la scena precedentă
     * @endcode
     *
     * @note Scenele trebuie să implementeze corect OnEnter/OnExit pentru a nu lăsa resurse sau stare inconsistentă la push/pop/replace.
     * @note SceneManager nu este thread-safe!
     * @note Folosește IsOverlay și BlocksInputBelow pentru a configura corect comportamentul de stacking și propagare input.
     *
     * @see IScene pentru contractul detaliat al interfeței de scenă.
     */
    class SceneManager
    {
    public:
        /**
         * @brief Creează un SceneManager gol.
         */
        SceneManager();

        /**
         * @brief Distruge SceneManager-ul și toate scenele din stivă.
         * Apelează OnExit pentru fiecare scenă din stivă, în ordine inversă (vârf spre bază).
         */
        ~SceneManager();

        // Nu permite copierea, permite mutarea
        SceneManager(const SceneManager &) = delete;
        SceneManager &operator=(const SceneManager &) = delete;
        SceneManager(SceneManager &&) = default;
        SceneManager &operator=(SceneManager &&) = default;

        /**
         * @brief Adaugă o scenă nouă peste cea curentă.
         *
         * Dacă scena precedentă bloca inputul (BlocksInputBelow == true), îi va fi apelat OnExit automat.
         * Noua scenă va primi OnEnter imediat după ce a fost adăugată pe stivă.
         *
         * @param scene Scena de adăugat (ownership transferat prin std::unique_ptr).
         */
        void PushScene(std::unique_ptr<IScene> scene);

        /**
         * @brief Scoate scena de pe vârf.
         *
         * Apelează OnExit pe scena scoasă, apoi (dacă există) reapelează OnEnter pe scena precedentă (doar dacă aceasta bloca inputul).
         *
         * @throws assert dacă stiva este goală.
         */
        void PopScene();

        /**
         * @brief Scoate toate scenele de pe vârf și adaugă una nouă.
         *
         * Apelează OnExit pentru fiecare scenă scoasă, apoi adaugă noua scenă și îi apelează OnEnter.
         * Util pentru a schimba complet starea aplicației (ex: la restart sau schimbare hard de stare).
         *
         * @param newScene Scena de pus pe vârf (ownership transferat).
         */
        void PopAllAndPush(std::unique_ptr<IScene> newScene);

        /**
         * @brief Înlocuiește scena de pe vârf cu una nouă.
         *
         * Apelează OnExit pe scena veche, apoi OnEnter pe cea nouă.
         * Dacă stiva e goală, doar se adaugă noua scenă și i se apelează OnEnter.
         *
         * @param scene Scena de pus pe vârf (ownership transferat).
         */
        void ReplaceScene(std::unique_ptr<IScene> scene);

        /**
         * @brief Șterge complet toate scenele din stivă.
         *
         * Apelează OnExit pentru fiecare scenă, de la vârf la bază.
         * Util pentru resetarea completă a jocului sau la încărcare hard de stare.
         */
        void Clear();

        /**
         * @brief Returnează scena de pe vârf (cea activă).
         *
         * @return Pointer la scena de pe vârf, sau nullptr dacă stiva este goală.
         */
        IScene *CurrentScene() const;

        /**
         * @brief Actualizează toate scenele active (overlay + scena solidă de la bază).
         *
         * Se parcurge stiva de la prima scenă solidă (IsOverlay == false), apoi toate overlay-urile de deasupra (IsOverlay == true).
         * Astfel, un dialog sau HUD va primi Update chiar dacă nu blochează inputul.
         *
         * @param dt Delta time (timpul scurs față de ultimul frame, în secunde).
         */
        void Update(float dt);

        /**
         * @brief Desenează toate scenele active (overlay + scena solidă).
         *
         * Se parcurge stiva de la prima scenă solidă (IsOverlay == false), apoi toate overlay-urile de deasupra.
         * Astfel, HUD-ul, dialogul sau pop-up-urile vor fi desenate peste scena principală.
         */
        void Draw();

        /**
         * @brief Returnează numărul de scene din stivă.
         * @return Numărul de scene (poate fi zero dacă nu există scene active).
         */
        size_t Size() const;

        /**
         * @brief Permite accesul readonly la stiva de scene (pentru debug, introspecție, UI etc).
         * @return Referință constantă la vectorul intern de unique_ptr<IScene>.
         */
        const std::vector<std::unique_ptr<IScene>> &GetStack() const;

    private:
        std::vector<std::unique_ptr<IScene>> scenes; //!< Stiva internă de scene (de la bază la vârf).

        /**
         * @brief Găsește indexul primei scene solide (IsOverlay == false), de la bază.
         *
         * Util pentru a determina de unde trebuie să înceapă Update/Draw când există overlay-uri multiple.
         * @return Indexul primei scene solide.
         */
        int FindFirstActiveIndex() const;
    };

} // namespace scene