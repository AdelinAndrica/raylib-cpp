#pragma once
#include <vector>
#include "tile.hpp"
#include "raylib.h"

class Map
{
public:
    Map(int width, int height, float tileSize);

    Tile &getTile(int x, int y);
    const Tile &getTile(int x, int y) const;
    bool isWalkable(int x, int y) const;
    void Draw() const;

    int width() const { return _width; }
    int height() const { return _height; }
    float getTileSize() const { return _tileSize; }

private:
    int _width, _height;
    float _tileSize;
    std::vector<std::vector<Tile>> tiles;
};