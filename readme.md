
# 🎮 JRPG Turn-Based Game – System Overview (for GitHub Copilot & Modular Design)

## 🔹 1. Core Engine (basic systems)
- Window + render system (Raylib init, render loop)
- Scene manager (switch între meniu, joc, luptă, dialog etc.)
- Config loader (JSON sau INI pentru setări audio/video)
- Game state (global state – salvări, flags, poziții, iteme etc.)
- Input manager (tastatură, controller)

---

## 🔹 2. Main Menu System
- Main menu scene (new game, continue, settings, quit)
- Load/Save file selector
- Settings UI (volume, fullscreen, lang etc.)
- Data serialization (JSON/binar – salvează starea jocului)

---

## 🔹 3. World Map & Exploration
- Tilemap loader (CSV sau Tiled `.tmx`)
- Player controller (mișcare pe grid sau liberă)
- Collision system (tiles, obstacole, zone)
- Portal system (treceri între hărți/zone)
- Random encounters + zona de trigger

---

## 🔹 4. Turn-Based Combat System
- Battle state machine (`Idle → PlayerTurn → EnemyTurn → End`)
- UI de luptă (comenzi, targetare, animații de atac)
- Sistem de skilluri + efecte
- Damage calculator
- Stat sistem: HP, MP, ATK, DEF, SPD, LUCK
- AI inamic simplu (heuristic sau random)

---

## 🔹 5. NPCs & Dialog
- Sistem de dialog JSON/scripted
- UI dialog cu portret și text (multi-line scroll)
- Interacțiune cu NPC + trigger condiții
- Branching dialog (alegeri morale, finaluri diferite)

---

## 🔹 6. Inventory, Stats & Equipment
- Inventar cu UI și sloturi
- Sistem de echipament (arme, armuri, accesorii)
- Consumabile (poțiuni, pergamente, etc.)
- Comparare iteme + UI pentru stats

---

## 🔹 7. Quest System
- Jurnal de questuri
- Condiții pentru progres (ex: obiecte, NPC, locație)
- Recompense + urmărire progres

---

## 🔹 8. Audio/FX System
- Background music (BGM) pe scenă
- Sunete pentru meniuri, atac, dialog
- Shader-based effects (ex: low health vignette, CRT overlay, bloom etc.)
