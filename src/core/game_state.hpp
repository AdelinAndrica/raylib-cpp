#pragma once
#include <memory>
#include "world/map.hpp"
#include "entities/player.hpp"

class GameState
{
public:
    static GameState &GetInstance()
    {
        static GameState instance;
        return instance;
    }

    std::unique_ptr<Map> currentMap;
    std::unique_ptr<Player> player;

private:
    GameState() = default;
    GameState(const GameState &) = delete;
    GameState &operator=(const GameState &) = delete;
    ~GameState() = default;
};

void InitGameState();