// include/ecs/EventBus.hpp
#pragma once

#include <functional>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <memory>
#include <any>

namespace ecs
{
    class ECSWorld; // Forward declaration for ECSWorld
}

class EventBus
{
public:
    EventBus() = default;
    ~EventBus() = default;

    template <typename EventType>
    void subscribe(std::function<void(const EventType &)> handler)
    {
        auto &handlers = subscribers[typeid(EventType)];
        handlers.push_back([handler](const void *event)
                           { handler(*static_cast<const EventType *>(event)); });
    }

    template <typename EventType>
    void emit(const EventType &event)
    {
        auto it = subscribers.find(typeid(EventType));
        if (it != subscribers.end())
        {
            for (auto &handler : it->second)
            {
                handler(static_cast<const void *>(&event));
            }
        }
    }

    void clear();

private:
    using HandlerFunc = std::function<void(const void *)>;
    std::unordered_map<std::type_index, std::vector<HandlerFunc>> subscribers;
};
