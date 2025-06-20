#pragma once

enum class TileType
{
    Empty = 0,
    Wall = 1
};

struct Tile
{
    TileType type = TileType::Empty;
    // Poți extinde cu sprite index, anim, etc.
};