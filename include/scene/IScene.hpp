#pragma once

#include <string>

namespace scene
{
    /**
     * @brief Interfață abstractă pentru toate scenele din joc.
     *
     * O scenă reprezintă o stare distinctă a aplicației (ex: Meniu Principal, Joc, Pauză, Dialog etc.).
     * Toate scenele concrete trebuie să derive din această interfață și să implementeze ciclul de viață al unei scene.
     *
     * Contractul public (documentație Doxygen):
     *
     * - OnEnter(): Este apelată automat când scena devine activă (ex: este adăugată pe stivă, înlocuiește o altă scenă etc.).
     *      - Folosită pentru inițializarea resurselor specifice scenei, resetarea stării interne sau pornirea efectelor de intrare.
     *
     * - OnExit(): Este apelată automat când scena iese din stivă sau este înlocuită de alta.
     *      - Folosită pentru cleanup, salvarea stării sau eliberarea resurselor.
     *
     * - Update(float dt): Actualizează logica scenei la fiecare frame.
     *      - Parametru dt: intervalul de timp (în secunde) față de ultimul frame (delta time).
     *      - Aici se tratează inputul, se actualizează entitățile/logica jocului și se gestionează trecerea la alte scene.
     *
     * - Draw(): Desenează scena pe ecran.
     *      - Aici se realizează desenarea completă a scenei curente (UI, entități, efecte etc.).
     *
     * - GetName(): (opțional) Returnează un nume unic pentru scenă, util pentru debug, logging sau identificare.
     *
     * - BlocksInputBelow(): (opțional) Specifică dacă această scenă interceptează complet inputul (true = scenă "solidă", false = overlay/transparentă).
     *      - Exemplu: Meniul de pauză ar trebui să blocheze inputul pentru gameplay-ul de dedesubt.
     *
     * - IsOverlay(): (opțional) Specifică dacă scena acționează ca un overlay peste celelalte (true = este desenată peste scenele de sub ea, false = acoperă complet).
     *      - Exemplu: Un dialog sau HUD poate fi overlay, în timp ce o tranziție de loading acoperă tot.
     *
     * Extensie: Metodele opționale au implementare default, ceea ce permite extinderea facilă a interfeței fără a rupe codul existent.
     */
    class IScene
    {
    public:
        /// Destructor virtual necesar pentru utilizarea corectă a polimorfismului.
        virtual ~IScene() = default;

        /**
         * @brief Cheamată când scena devine activă sau este adăugată pe stivă.
         * Ideal pentru inițializarea resurselor sau resetarea stării.
         */
        virtual void OnEnter() = 0;

        /**
         * @brief Cheamată când scena iese din stivă sau este înlocuită.
         * Folosită pentru cleanup sau salvarea stării.
         */
        virtual void OnExit() = 0;

        /**
         * @brief Actualizează logica scenei pentru fiecare frame.
         * @param dt Delta time (secunde) față de ultimul frame.
         */
        virtual void Update(float dt) = 0;

        /**
         * @brief Desenează scena pe ecran.
         */
        virtual void Draw() = 0;

        /**
         * @brief Returnează un nume unic pentru scenă (util pentru debug și logging).
         * @return Numele scenei (implicit: "UnnamedScene").
         */
        virtual std::string GetName() const { return "UnnamedScene"; }

        /**
         * @brief Specifică dacă scena blochează inputul pentru scenele de sub ea.
         * @return true dacă blochează, false dacă permite propagarea inputului (implicit: true).
         */
        virtual bool BlocksInputBelow() const { return true; }

        /**
         * @brief Specifică dacă scena se comportă ca overlay peste celelalte (ex: dialog, HUD).
         * @return true pentru overlay, false pentru scenă completă (implicit: false).
         */
        virtual bool IsOverlay() const { return false; }
    };
} // namespace scene