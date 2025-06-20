#pragma once
#include <vector>
#include "tile.hpp"

class Map
{
public:
    Map(int width, int height);
    Tile &getTile(int x, int y);
    bool isWalkable(int x, int y) const;
    // + load/unload logic...

private:
    int width, height;
    std::vector<std::vector<Tile>> tiles;
};