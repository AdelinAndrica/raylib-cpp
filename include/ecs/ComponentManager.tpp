#pragma once

#include <cstddef>

namespace ecs
{
    template <typename T, typename EntityID>
    ComponentManager<T, EntityID>::ComponentManager() = default;

    template <typename T, typename EntityID>
    ComponentManager<T, EntityID>::~ComponentManager() = default;

    template <typename T, typename EntityID>
    void ComponentManager<T, EntityID>::addComponent(EntityID entity, const T &component)
    {
        components_[entity] = component;
    }

    template <typename T, typename EntityID>
    void ComponentManager<T, EntityID>::removeComponent(EntityID entity)
    {
        components_.erase(entity);
    }

    template <typename T, typename EntityID>
    T *ComponentManager<T, EntityID>::getComponent(EntityID entity)
    {
        auto it = components_.find(entity);
        return (it != components_.end()) ? &(it->second) : nullptr;
    }

    template <typename T, typename EntityID>
    const T *ComponentManager<T, EntityID>::getComponent(EntityID entity) const
    {
        auto it = components_.find(entity);
        return (it != components_.end()) ? &(it->second) : nullptr;
    }

    template <typename T, typename EntityID>
    bool ComponentManager<T, EntityID>::hasComponent(EntityID entity) const
    {
        return components_.find(entity) != components_.end();
    }

    template <typename T, typename EntityID>
    void ComponentManager<T, EntityID>::onEntityDestroyed(EntityID entity)
    {
        removeComponent(entity);
    }

    template <typename T, typename EntityID>
    void ComponentManager<T, EntityID>::clear()
    {
        components_.clear();
    }

    template <typename T, typename EntityID>
    typename ComponentManager<T, EntityID>::iterator ComponentManager<T, EntityID>::begin()
    {
        return components_.begin();
    }

    template <typename T, typename EntityID>
    typename ComponentManager<T, EntityID>::iterator ComponentManager<T, EntityID>::end()
    {
        return components_.end();
    }

    template <typename T, typename EntityID>
    typename ComponentManager<T, EntityID>::const_iterator ComponentManager<T, EntityID>::begin() const
    {
        return components_.begin();
    }

    template <typename T, typename EntityID>
    typename ComponentManager<T, EntityID>::const_iterator ComponentManager<T, EntityID>::end() const
    {
        return components_.end();
    }

    template <typename T, typename EntityID>
    std::size_t ComponentManager<T, EntityID>::size() const
    {
        return components_.size();
    }
} // namespace ecs