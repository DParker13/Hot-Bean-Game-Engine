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
    EntityManager::EntityManager(std::shared_ptr<LoggingManager> logging_manager)
        : m_logging_manager(logging_manager) {

        m_logging_manager->Log(LoggingType::DEBUG, "Initializing EntityManager");

        // Initializing available entities queue based on MAX_ENTITIES
        for (Entity entity_id = 0; entity_id < MAX_ENTITIES; entity_id++) {
            m_available_entities.push(entity_id);
        }

        m_logging_manager->Log(LoggingType::DEBUG, "Initialized " + std::to_string(m_available_entities.size()) + " Entities");
    }

    /**
     * Creates a new entity and returns its unique identifier.
     *
     * @return The unique identifier of the newly created entity.
     *
     * @throws assertion failure if the maximum number of entities has been reached.
     */
    Entity EntityManager::CreateEntity() {
        assert(m_living_entity_count < MAX_ENTITIES && "Too many entities in existence.");

        // Take an ID from the front of the queue
        Entity id = m_available_entities.front();

        m_logging_manager->Log(LoggingType::DEBUG, "Creating Entity \"" + std::to_string(id) + "\"");

        m_available_entities.pop();
        ++m_living_entity_count;

        m_logging_manager->Log(LoggingType::DEBUG, "Entity \"" + std::to_string(id) + "\" created.");
        m_logging_manager->Log(LoggingType::DEBUG, "\tLiving Entities: " + std::to_string(m_living_entity_count));
        m_logging_manager->Log(LoggingType::DEBUG, "\tAvailable Entities: " + std::to_string(m_available_entities.size()));

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

        m_logging_manager->Log(LoggingType::DEBUG, "Destroying Entity \"" + std::to_string(entity) + "\"...");

        // Invalidate the destroyed entity's signature
        m_signatures[entity].reset();

        // Place the destroyed entity ID at the back of the queue
        m_available_entities.push(entity);
        --m_living_entity_count;

        m_logging_manager->Log(LoggingType::DEBUG, "Entity \"" + std::to_string(entity) + "\" destroyed.");
        m_logging_manager->Log(LoggingType::DEBUG, "\tLiving Entities: " + std::to_string(m_living_entity_count));
        m_logging_manager->Log(LoggingType::DEBUG, "\tAvailable Entities: " + std::to_string(m_available_entities.size()));
    }

    /**
     * Sets the signature for a given entity.
     *
     * @param entity The ID of the entity to set the signature for.
     * @param component_type The signature to be set for the entity.
     *
     * @throws assertion failure if the entity ID is out of range.
     */
    Signature EntityManager::SetSignature(Entity entity, ComponentType component_type) {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        // Set the signature for the given entity
        m_signatures[entity].set(component_type);

        m_logging_manager->Log(LoggingType::DEBUG, "Entity \"" + std::to_string(entity) + "\""
            " signature set \"" + m_signatures[entity].to_string() + "\"");

        return m_signatures[entity];
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

        return m_signatures[entity];
    }

    bool EntityManager::HasComponentType(Entity entity, ComponentType component_type) {
        return GetSignature(entity).test(component_type);
    }

    Entity EntityManager::EntityCount() const {
        return m_living_entity_count;
    }

    EntityManager::~EntityManager() = default;
}