#pragma once

enum class TileType
{
    Empty = 0,
    Wall = 1,
    Door = 2,
    Edge = 3,
    Trigger = 4
};

struct Tile
{
    TileType type = TileType::Empty;
    // Pentru trigger/door/edge: poți adăuga și un payload (ex: id, target, script etc)
    int transitionTarget = -1; // id sau index către altă hartă/zona
    // sau std::string eventName/targetMap etc, dacă vrei mai flexibil
};