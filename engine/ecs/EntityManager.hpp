#pragma once
#include <cstdint>
#include <queue>
#include <vector>

/**
 * @brief Alias for entity IDs.
 */
using EntityID = std::uint32_t;

/**
 * @brief Manages creation, destruction, and validation of ECS entities.
 *
 * Provides unique IDs for entities, supports recycling of IDs, and can reset all state.
 */
class EntityManager
{
public:
    /**
     * @brief Construct a new EntityManager object.
     */
    EntityManager();

    /**
     * @brief Create a new entity and return its unique ID.
     * @return EntityID Unique identifier for the new entity.
     */
    EntityID createEntity();

    /**
     * @brief Destroy an entity by its ID. Its ID may be recycled.
     * @param id The ID of the entity to destroy.
     */
    void destroyEntity(EntityID id);

    /**
     * @brief Check if a given entity ID is valid and currently active.
     * @param id Entity ID to check.
     * @return true if the entity exists and is active.
     * @return false otherwise.
     */
    bool isValid(EntityID id) const;

    /**
     * @brief Destroy all entities and reset ID counters.
     */
    void reset();

    /**
     * @brief Get the number of currently living (active) entities.
     * @return std::size_t The count of active entities.
     */
    std::size_t livingEntities() const;

private:
    EntityID nextID;              ///< Next ID to be allocated if no free IDs.
    std::queue<EntityID> freeIDs; ///< Queue of recycled IDs.
    std::vector<bool> active;     ///< Activity flag for each ID.
};