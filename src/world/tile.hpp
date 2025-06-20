#pragma once

enum class TileType
{
    Empty,
    Wall,
    Door,
    Trigger
};

struct Tile
{
    TileType type;
    bool walkable;

    Tile(TileType t = TileType::Empty)
        : type(t), walkable(t != TileType::Wall) {}
};