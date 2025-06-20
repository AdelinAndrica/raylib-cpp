#pragma once
#include <memory>
#include <vector>
#include "world/map.hpp"
#include "entities/player.hpp"
#include "entities/entity.hpp"

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
    std::vector<Entity *> entities;

    void Init();
    void Update();
    void Draw();

private:
    GameState() = default;
    GameState(const GameState &) = delete;
    GameState &operator=(const GameState &) = delete;
    ~GameState() = default;
};
