// include/ecs/ECSWorld.hpp
#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <memory>
#include <typeindex>
#include <cstdint>
#include <tuple>
#include "ComponentStorage.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"
#include "EventBus.hpp"
#include "System.hpp"

using Entity = std::uint32_t;

// =================== Forward declarations ===================
template <typename T>
class ComponentStorage;
class EntityManager;
class EventBus;
class ISystem;
namespace ecs
{

    // =================== ECSWorld ===================
    class ECSWorld
    {
    public:
        ECSWorld();

        EventBus &getEventBus() { return eventBus; }
        SystemManager &getSystemManager();

        Entity createEntity();
        void destroyEntity(Entity e);

        template <typename T>
        ComponentStorage<T> &getStorage();

        template <typename T>
        void addComponent(Entity e, const T &c);

        template <typename T>
        void removeComponent(Entity e);

        template <typename... Components, typename Func>
        void view(Func &&f);

        bool isAlive(Entity e) const;

        template <typename T>
        void addSystem(std::shared_ptr<T> system, SystemPhase phase)
        {
            getSystemManager().registerSystem(system, phase);
        }

        void configureSystems();
        void updateSystems(float dt, SystemPhase phase);

    private:
        EventBus eventBus;
        std::unique_ptr<SystemManager> systemManager = std::make_unique<SystemManager>();

        class IComponentRemover
        {
        public:
            virtual void remove(Entity e) = 0;
            virtual ~IComponentRemover() = default;
        };

        template <typename T>
        class ComponentStorageWrapper;

        EntityManager *em;
        std::unordered_map<std::type_index, std::shared_ptr<void>> storages;
    };

    // =================== Template implementations ===================
    template <typename T>
    ComponentStorage<T> &ECSWorld::getStorage()
    {
        auto idx = std::type_index(typeid(T));
        if (!storages[idx])
        {
            storages[idx] = std::make_shared<ComponentStorage<T>>();
        }
        return *std::static_pointer_cast<ComponentStorage<T>>(storages[idx]);
    }

    template <typename T>
    void ECSWorld::addComponent(Entity e, const T &c)
    {
        getStorage<T>().add(e, c);
    }

    template <typename T>
    void ECSWorld::removeComponent(Entity e)
    {
        getStorage<T>().remove(e);
    }

    template <typename... Components, typename Func>
    void ECSWorld::view(Func &&f)
    {
        auto &base = getStorage<std::tuple_element_t<0, std::tuple<Components...>>>();
        for (Entity e : base.entities())
        {
            if ((getStorage<Components>().has(e) && ...))
            {
                f(e, getStorage<Components>().get(e)...);
            }
        }
    }

    // ComponentStorageWrapper specializations
    template <typename T>
    class ECSWorld::ComponentStorageWrapper : public ComponentStorage<T>, public ECSWorld::IComponentRemover
    {
    public:
        void remove(Entity e) override
        {
            ComponentStorage<T>::remove(e);
        }
    };
}
