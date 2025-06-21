# VeinEngine

**VeinEngine** este un engine de joc modular, dezvoltat în C++ peste [raylib](https://www.raylib.com/), orientat pe performanță, flexibilitate și ușurință în utilizare, cu accent pe separarea clară între logică, randare și sisteme de joc. Engine-ul folosește un sistem ECS (Entity Component System) centralizat (ECSWorld) pentru gestionarea entităților, componentelor și sistemelor, permițând dezvoltarea rapidă a jocurilor 2D/2.5D cu scene complexe și gameplay dinamic.

## Caracteristici principale VeinEngine

- **ECS (Entity Component System) Centralizat:**  
  Un World unic ce gestionează toate entitățile, componentele și sistemele, facilitând modularitatea și reutilizarea codului.
- **Sistem de Scene și SceneManager:**  
  Scenele sunt gestionate dinamic, cu suport pentru comutare rapidă și transfer de stare între scene.
- **Integrare raylib:**  
  Acces rapid la funcționalitățile raylib pentru randare, input, audio și asset management.
- **Modularitate:**  
  Separare clară între subsisteme: ECS, render, input, audio, asset management.
- **Testabilitate și extensibilitate:**  
  Codul este structurat pentru a permite testare facilă și extindere cu noi sisteme sau componente.
- **Serializare/Deserializare (opțional):**  
  Pregătit pentru persistența stării jocului sau încărcarea/descărcarea rapidă a scenelor.

---

# Ashen Veins – Descriere joc

**Ashen Veins** este un action RPG 2D dezvoltat cu VeinEngine, plasat într-un univers dark fantasy unde jucătorul explorează o lume coruptă de forțe necunoscute. Jocul pune accent pe explorare, combat strategic și luarea de decizii cu impact pe termen lung.

## Caracteristici principale Ashen Veins

- **Explorare narativă:**  
  Jucătorul descoperă mistere și povestea lumii Ashen Veins prin interacțiuni cu personaje, explorarea mediului și descoperirea de secrete.
- **Combat tactic:**  
  Sistem de luptă axat pe timing, poziționare și folosirea eficientă a abilităților și resurselor.
- **Sisteme RPG:**  
  Dezvoltarea personajului prin abilități, echipamente și alegeri morale.
- **Atmosferă dark fantasy:**  
  Grafică stilizată și sound design care creează o atmosferă apăsătoare, tensionată.
- **Progresie modulară:**  
  Fiecare zonă este o scenă distinctă, gestionată de SceneManager-ul engine-ului, permițând tranziții fluide și evenimente contextuale.

---

## Structură proiect

- `engine/` – Cod sursă pentru subsistemele de bază ale engine-ului (ecs, render, input, audio, etc.)
- `include/` – Header files pentru engine.
- `game/` – Cod sursă specific jocului Ashen Veins (scene, entități, componente, sisteme de joc).
- `assets/` – Resurse: sprites, tilemaps, sunete, fonturi, etc.

---

## Cum rulezi proiectul?

1. **Clonează repository-ul:**
   ```sh
   git clone https://github.com/AdelinAndrica/raylib-cpp.git
   ```
2. **Build & Run:**
   - Asigură-te că ai instalat [raylib](https://www.raylib.com/) și un compilator C++ compatibil.
   - Folosește CMake sau Makefile-ul din proiect:
     ```sh
     cd raylib-cpp
     mkdir build && cd build
     cmake ..
     make
     ./AshenVeins
     ```

---

## Roadmap

- [x] Sistem ECS centralizat (ECSWorld)
- [x] SceneManager și sisteme de scene
- [ ] Integrare completă gameplay (combat, inventory, AI, etc.)
- [ ] Serializare/deserializare stări joc
- [ ] Editor de nivel integrat
- [ ] Export multi-platformă

---

## Contribuie!

Orice contribuție este binevenită! Vezi [CONTRIBUTING.md](CONTRIBUTING.md) pentru detalii despre stil, workflow și reguli de pull request.

---

## Licență

VeinEngine și Ashen Veins sunt distribuite sub licența MIT.  
Vezi [LICENSE](LICENSE) pentru detalii.

---