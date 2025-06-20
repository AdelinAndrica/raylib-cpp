#include "map.hpp"

Map::Map(int width, int height, float tileSize)
    : _width(width), _height(height), _tileSize(tileSize),
      tiles(height, std::vector<Tile>(width, Tile{}))
{
    // Exemplu: pune un Wall la (3,3)
    if (width > 3 && height > 3)
        tiles[3][3].type = TileType::Wall;

    tiles[1][0].type = TileType::Edge; // margine stânga = edge
    tiles[5][5].type = TileType::Door;
    tiles[5][5].transitionTarget = 2; // id-ul camerei/zonei țintă
    tiles[3][3].type = TileType::Trigger;
    tiles[3][3].transitionTarget = 42; // id-ul evenimentului
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
    return tiles[y][x].type != TileType::Wall;
}

bool Map::isTransition(int x, int y) const
{
    const Tile &t = getTile(x, y);
    return t.type == TileType::Door || t.type == TileType::Edge || t.type == TileType::Trigger;
}

TileType Map::getTransitionType(int x, int y) const
{
    return getTile(x, y).type;
}

int Map::getTransitionTarget(int x, int y) const
{
    return getTile(x, y).transitionTarget;
}

void Map::Draw() const {
    for (int y = 0; y < _height; ++y) {
        for (int x = 0; x < _width; ++x) {
            Color c = LIGHTGRAY;
            switch (tiles[y][x].type) {
                case TileType::Wall: c = DARKGRAY; break;
                case TileType::Door: c = BLUE; break;
                case TileType::Edge: c = GREEN; break;
                case TileType::Trigger: c = YELLOW; break;
                default: break;
            }
            DrawRectangle(x * _tileSize, y * _tileSize, _tileSize, _tileSize, c);
            DrawRectangleLines(x * _tileSize, y * _tileSize, _tileSize, _tileSize, BLACK);
        }
    }
}