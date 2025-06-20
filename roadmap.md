# 2D JRPG + Game Engine: Roadmap Actualizat (2025)

---

## Viziune și Principii

- **Engine modular și reutilizabil**, cu separare clară de codul de joc.
- **Arhitectură Entity-Component-System (ECS)** ca bază pentru toate subsistemele.
- **Scene Management** peste ECS, cu flow flexibil între scene (meniuri, lume, bătălii, etc).
- **Folder structure la rădăcină:** `/engine`, `/game`, `/include`, `/external`, `/tests`, `/docs`, `/assets`, `/scripts`.
- **Best practices:** compoziție, testare, documentare, no singletons, modularitate.

---

## Faze de Dezvoltare

### Faza 1: Foundation & Refactoring

- [ ] **Implementare și testare ECS de bază**
  - `EntityManager`, `ComponentManager`, `SystemManager`, `ECSRegistry`
  - Teste unitare pentru fiecare subsistem ECS
  - Documentație și exemple de utilizare (în `/docs`)

- [ ] **Restructurare Directorii**
  - Mută codul engine în `/engine`, codul de joc în `/game`
  - Adaugă `/include` pentru headere publice, `/external` pentru dependențe, `/scripts` pentru build/ci, `/tests`, `/docs`, `/assets`
  - Update la README și roadmap

- [ ] **Scene Management peste ECS**
  - SceneManager cu stivă de scene (push/pop/replace)
  - Scene concrete: MainMenu, Overworld, Battle, Pause, Dialogue
  - Fiecare scenă poate avea propriul ECSRegistry sau partajat

---

### Faza 2: Engine Systems & Tooling

- [ ] **Sisteme Engine ca Module**
  - Rendering, Input, Audio, Resource Management ca sisteme ECS sau servicii injectabile
  - Refactorizează sisteme existente (Coliziuni, Render, Input) să opereze pe ECS

- [ ] **Data-driven Content**
  - Formate JSON/YAML pentru entități, hărți, iteme, dialog, etc.
  - Data loaders și hot-reload

- [ ] **Testare și Documentare**
  - Teste automate pentru fiecare modul
  - Documentează extensia engine-ului, flow-ul scenelor, exemplu vertical slice în `/docs`

---

### Faza 3: Core Gameplay Systems (JRPG Layer)

- [ ] **Gameplay ca Sisteme ECS**
  - Inventory, Actor/Party, Quest, Dialogue, Battle ca sisteme și componente ECS
  - UI/HUD, map transitions, trigger events

- [ ] **Save/Load System**
  - Serializare ECS state, sloturi de salvare, UI pentru save/load

---

### Faza 4: Polish, Content & Open Source

- [ ] **Conținut demo** (hărți, NPC, dialog, bătălii, inventory)
- [ ] **Unelte de editare și debugging tools** (opțional)
- [ ] **Documentație pentru engine și exemple de extensie**
- [ ] **Pregătire open source:** LICENSE, CONTRIBUTING, issue templates

---

## Structură Exemplu (actualizată)

```
/engine/        # Engine generic (ecs, render, audio, input, resource, etc.)
/game/          # Cod de joc concret (scenes, systems, data, gameplay logic)
/include/       # Header files publice pentru engine
/external/      # Biblioteci terțe (ex: raylib)
/tests/         # Teste unitare și de integrare
/docs/          # Documentație engine și exemplu de extensie
/assets/        # Resurse (sprites, tilesets, sunete, maps, etc.)
/scripts/       # Scripturi pentru build, test, format, ci
CMakeLists.txt
README.md
```

---

## Milestone Breakdown (Sugestie)

1. ECS core + restructurare engine/game
2. Scene manager & basic scenes
3. Refactor sisteme principale la ECS (render, input, collision)
4. Data-driven content & loaders
5. Gameplay systems: party, inventory, quest, battle
6. UI/HUD, save/load, polish
7. Testare, demo, documentare, open source

---

## Tips & Best Practices

- **Iterează pe vertical slice**: overworld → battle → reward → back to map
- **Separă engine/game**: nu amesteca logica specifică jocului cu engine-ul
- **Testează și documentează**: la fiecare pas, adaugă teste și exemple
- **No singletons / global state**: folosește dependency injection/context explicit
- **Optimizează după ce ai flow funcțional**
- **Folosește scripturi automate pentru build/test/format**

---

**Ready to build? Lucrează incremental pe branch-ul `feat(ecs-conversion)` și documentează fiecare pas major!**