/**
 * @file entity_manager.cpp
 * @author Daniel Parker (DParker13)
 * @brief Manages the creation and destruction of entities.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "entity_manager.hpp"

namespace Core::Managers {
    /**
     * Constructs an EntityManager and initializes the queue of available entity IDs.
     * 
     * This constructor fills the queue with all possible entity IDs, making them 
     * available for future use. The entity IDs range from 0 to MAX_ENTITIES - 1.
     */
    EntityManager::EntityManager() {
        for (Entity entityId = 0; entityId < MAX_ENTITIES; entityId++) {
            _availableEntities.push(entityId);
        }
    }

    /**
     * Creates a new entity and returns its unique identifier.
     *
     * @return The unique identifier of the newly created entity.
     *
     * @throws assertion failure if the maximum number of entities has been reached.
     */
    Entity EntityManager::CreateEntity() {
        assert(_livingEntityCount < MAX_ENTITIES && "Too many entities in existence.");

        // Take an ID from the front of the queue
        Entity id = _availableEntities.front();
        _availableEntities.pop();
        ++_livingEntityCount;

        return id;
    }

    /**
     * Destroys an entity and makes its ID available for reuse.
     *
     * @param entity The ID of the entity to be destroyed.
     *
     * @throws assertion failure if the entity ID is out of range.
     */
    void EntityManager::DestroyEntity(Entity entity) {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        // Invalidate the destroyed entity's signature
        _signatures[entity].reset();

        // Place the destroyed entity ID at the back of the queue
        _availableEntities.push(entity);
        --_livingEntityCount;
    }

    /**
     * Sets the signature for a given entity.
     *
     * @param entity The ID of the entity to set the signature for.
     * @param componentType The signature to be set for the entity.
     *
     * @throws assertion failure if the entity ID is out of range.
     */
    Signature EntityManager::SetSignature(Entity entity, ComponentType componentType) {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        // Set the signature for the given entity
        _signatures[entity].set(componentType);

        return _signatures[entity];
    }

    /**
     * Retrieves the signature associated with a given entity.
     *
     * @param entity The ID of the entity to retrieve the signature for.
     *
     * @return The signature associated with the given entity.
     *
     * @throws assertion failure if the entity ID is out of range.
     */
    Signature EntityManager::GetSignature(Entity entity) {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        // Return the signature for the given entity
        return _signatures[entity];
    }

    Entity EntityManager::EntityCount() const {
        return _livingEntityCount;
    }

    /**
     * Prints the contents of ComponentManager to the console. This is mostly for
     * debugging purposes and should be removed in a production build.
     */
    std::string EntityManager::ToString() const {
        std::stringstream str;
        str << "Entity Manager:\n";
        str << "  Living Entity Count: " << _livingEntityCount << "\n";

        for (Entity i = 0; i < _livingEntityCount; i++) {
            str << "    Entity: " << i << "\n";
            str << "    Signature: " << _signatures[i] << "\n";
        }

        str << "\n";

        return str.str();
    }

    EntityManager::~EntityManager() = default;
}