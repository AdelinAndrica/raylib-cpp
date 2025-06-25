#include "ecs/ECSWorld.hpp"
#include "Logger.hpp"

// Exemplu pentru componente simple Position și Velocity
#include "Position.hpp"
#include "Velocity.hpp"

using json = nlohmann::json;

json ecs::ECSWorld::Serialize() const
{
    json j;
    // Serializare entități
    std::vector<Entity> entities;
    for (Entity e = 1; e < 10000; ++e) // exemplu: range fix, poți itera altfel dacă ai API
        if (isAlive(e))
            entities.push_back(e);
    j["entities"] = entities;

    // Serializare componente Position
    {
        const auto &storage = getStorage<Position>().raw();
        json arr = json::array();
        for (const auto &[e, pos] : storage)
            arr.push_back({{"entity", e}, {"x", pos.x}, {"y", pos.y}});
        j["Position"] = arr;
    }
    // Serializare componente Velocity
    {
        const auto &storage = getStorage<Velocity>().raw();
        json arr = json::array();
        for (const auto &[e, vel] : storage)
            arr.push_back({{"entity", e}, {"dx", vel.dx}, {"dy", vel.dy}});
        j["Velocity"] = arr;
    }
    // Adaugă aici alte componente după același pattern

    LOG_INFO("ECSWorld serializat cu " + std::to_string(entities.size()) + " entități.");
    return j;
}

void ecs::ECSWorld::Deserialize(const json &j)
{
    // Resetare lume
    // ... (poți adăuga API de reset dacă vrei)
    // Entități
    if (j.contains("entities"))
    {
        for (auto e : j["entities"])
            createEntity(); // sau creează cu ID dacă ai nevoie
    }
    // Componente Position
    if (j.contains("Position"))
    {
        for (const auto &item : j["Position"])
        {
            Entity e = item["entity"];
            Position pos{item["x"], item["y"]};
            addComponent<Position>(e, pos);
        }
    }
    // Componente Velocity
    if (j.contains("Velocity"))
    {
        for (const auto &item : j["Velocity"])
        {
            Entity e = item["entity"];
            Velocity vel{item["dx"], item["dy"]};
            addComponent<Velocity>(e, vel);
        }
    }
    // Adaugă aici alte componente după același pattern

    LOG_INFO("ECSWorld deserializat din JSON.");
}