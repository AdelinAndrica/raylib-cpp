#pragma once
#include "map.hpp"

class World
{
public:
    World();
    Map &getCurrentMap();
    void transitionToMap(int mapId);
    // + event/zone management...

private:
    std::vector<Map> maps;
    int currentMapIndex;
};