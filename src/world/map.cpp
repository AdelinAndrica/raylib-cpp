#include "map.hpp"

Map::Map(int width, int height, float tileSize)
    : _width(width), _height(height), _tileSize(tileSize),
      tiles(height, std::vector<Tile>(width, Tile{}))
{
    // Exemplu: pune un Wall la (3,3)
    if (width > 3 && height > 3)
        tiles[3][3].type = TileType::Wall;
}

Tile &Map::getTile(int x, int y)
{
    return tiles[y][x];
}

const Tile &Map::getTile(int x, int y) const
{
    return tiles[y][x];
}

bool Map::isWalkable(int x, int y) const
{
    if (x < 0 || y < 0 || x >= _width || y >= _height)
        return false;
    return tiles[y][x].type == TileType::Empty;
}

void Map::Draw() const
{
    for (int y = 0; y < _height; ++y)
    {
        for (int x = 0; x < _width; ++x)
        {
            Color c = (tiles[y][x].type == TileType::Empty) ? LIGHTGRAY : DARKGRAY;
            DrawRectangle(x * _tileSize, y * _tileSize, _tileSize, _tileSize, c);
            DrawRectangleLines(x * _tileSize, y * _tileSize, _tileSize, _tileSize, BLACK);
        }
    }
}