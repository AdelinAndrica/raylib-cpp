#pragma once
#include <unordered_map>
#include <cstdint>
#include <iterator>
#include <cstddef>

/**
 * @file ComponentManager.hpp
 * @brief Defines the ecs::ComponentManager class template for managing components.
 */

namespace ecs
{

    /**
     * @class ComponentManager
     * @brief Template class to manage components of type T for entities identified by EntityID.
     * @tparam T The component type to be managed.
     * @tparam EntityID The type used for entity identifiers. Defaults to std::uint32_t.
     */
    template <typename T, typename EntityID = std::uint32_t>
    class ComponentManager
    {
    public:
        /// Alias for the internal map type storing entity-component pairs.
        using MapType = std::unordered_map<EntityID, T>;
        /// Iterator type for the component map.
        using iterator = typename MapType::iterator;
        /// Const iterator type for the component map.
        using const_iterator = typename MapType::const_iterator;

        /**
         * @brief Construct a new ComponentManager object.
         */
        ComponentManager();

        /**
         * @brief Destroy the ComponentManager object.
         */
        ~ComponentManager();

        /**
         * @brief Add a component to the specified entity.
         * @param entity The ID of the entity to which the component will be added.
         * @param component The component to be added.
         */
        void addComponent(EntityID entity, const T &component);

        /**
         * @brief Remove the component associated with the specified entity.
         * @param entity The ID of the entity whose component will be removed.
         */
        void removeComponent(EntityID entity);

        /**
         * @brief Get a pointer to the component associated with the specified entity.
         * @param entity The ID of the entity whose component is requested.
         * @return Pointer to the component if found, otherwise nullptr.
         */
        T *getComponent(EntityID entity);

        /**
         * @brief Get a const pointer to the component associated with the specified entity.
         * @param entity The ID of the entity whose component is requested.
         * @return Const pointer to the component if found, otherwise nullptr.
         */
        const T *getComponent(EntityID entity) const;

        /**
         * @brief Check if the specified entity has an associated component.
         * @param entity The ID of the entity to check.
         * @return True if the component exists, false otherwise.
         */
        bool hasComponent(EntityID entity) const;

        /**
         * @brief Callback for when an entity is destroyed; removes its component if it exists.
         * @param entity The ID of the entity being destroyed.
         */
        void onEntityDestroyed(EntityID entity);

        /**
         * @brief Remove all components managed by this ComponentManager.
         */
        void clear();

        /**
         * @brief Get an iterator to the beginning of the components map.
         * @return Iterator to the first component.
         */
        iterator begin();

        /**
         * @brief Get an iterator to the end of the components map.
         * @return Iterator to one past the last component.
         */
        iterator end();

        /**
         * @brief Get a const iterator to the beginning of the components map.
         * @return Const iterator to the first component.
         */
        const_iterator begin() const;

        /**
         * @brief Get a const iterator to the end of the components map.
         * @return Const iterator to one past the last component.
         */
        const_iterator end() const;

        /**
         * @brief Get the number of components currently managed.
         * @return Number of components.
         */
        std::size_t size() const;

    private:
        /// Internal storage for entity-component pairs.
        MapType components_;
    };

} // namespace ecs
#include <ecs/ComponentManager.tpp>