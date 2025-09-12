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

namespace HBE::Managers {
    /**
     * Constructs an EntityManager and initializes the queue of available entity IDs.
     * 
     * This constructor fills the queue with all possible entity IDs, making them 
     * available for future use. The entity IDs range from 0 to MAX_ENTITIES - 1.
     */
    EntityManager::EntityManager(std::shared_ptr<LoggingManager> logging_manager)
        : m_logging_manager(logging_manager) {

        LOG_CORE(LoggingType::DEBUG, "Initializing EntityManager");

        InitializeEntityQueue();

        LOG_CORE(LoggingType::DEBUG, "Initialized " + std::to_string(m_available_entities.size()) + " Entities (starting at 0)");
    }

    EntityManager::~EntityManager() = default;

    /**
     * @brief Initializes the queue with available entity IDs.
     * 
     * Fills the queue with all possible entity IDs, making them 
     * available for future use. The entity IDs range from 0 to MAX_ENTITIES - 1.
     */
    void EntityManager::InitializeEntityQueue() {
        for (Entity entity_id = 0; entity_id < MAX_ENTITIES; entity_id++) {
            m_available_entities.push(entity_id);
            m_alive_entities[entity_id] = false;
        }
    }

    /**
     * @brief Creates a new entity and returns its unique identifier.
     *
     * @return The unique identifier of the newly created entity.
     * @throw std::overflow_error if the maximum number of entities has been reached.
     */
    Entity EntityManager::CreateEntity() {
        if (m_living_entity_count >= MAX_ENTITIES) {
            auto ex = std::overflow_error("Too many entities in existence.");
            LOG_CORE(LoggingType::ERROR, ex.what());
            throw ex;
        }

        // Take an ID from the front of the queue
        Entity id = m_available_entities.front();
        m_alive_entities[id] = true;

        LOG_CORE(LoggingType::DEBUG, "Creating Entity \"" + std::to_string(id) + "\"");

        m_available_entities.pop();
        ++m_living_entity_count;

        LOG_CORE(LoggingType::DEBUG, "Entity \"" + std::to_string(id) + "\" created.");
        LOG_CORE(LoggingType::DEBUG, "\tLiving Entities: " + std::to_string(m_living_entity_count));
        LOG_CORE(LoggingType::DEBUG, "\tAvailable Entities: " + std::to_string(m_available_entities.size() - 1));

        return id;
    }

    /**
     * @brief Destroys an entity and makes its ID available for reuse.
     *
     * @param entity The ID of the entity to be destroyed.
     * @throw std::out_of_range if the entity ID is out of range.
     */
    void EntityManager::DestroyEntity(Entity entity) {
        if (entity < 0 || entity >= MAX_ENTITIES) {
            std::out_of_range ex = std::out_of_range("Entity out of range.");
            LOG_CORE(LoggingType::ERROR, ex.what());
            throw ex;
        }

        // If the entity is not alive, return
        if (!m_alive_entities[entity]) return;

        LOG_CORE(LoggingType::DEBUG, "Destroying Entity \"" + std::to_string(entity) + "\"...");

        // Invalidate the destroyed entity's signature
        m_signatures[entity].reset();

        // Place the destroyed entity ID at the back of the queue
        m_available_entities.push(entity);
        m_alive_entities[entity] = false;
        --m_living_entity_count;

        LOG_CORE(LoggingType::DEBUG, "Entity \"" + std::to_string(entity) + "\" destroyed.");
        LOG_CORE(LoggingType::DEBUG, "\tLiving Entities: " + std::to_string(m_living_entity_count));
        LOG_CORE(LoggingType::DEBUG, "\tAvailable Entities: " + std::to_string(m_available_entities.size()));
    }

    /**
     * Sets the signature for a given entity.
     *
     * @param entity The ID of the entity to set the signature for.
     * @param component_type The signature to be set for the entity.
     * @return The signature of the entity.
     * @throw std::out_of_range if the entity ID is out of range.
     */
    Signature EntityManager::SetSignature(Entity entity, ComponentType component_type) {
        if (entity < 0 || entity >= MAX_ENTITIES) {
            std::out_of_range ex = std::out_of_range("Entity out of range.");
            LOG_CORE(LoggingType::ERROR, ex.what());
            throw ex;
        }

        // Set the signature for the given entity
        m_signatures[entity].set(component_type);

        LOG_CORE(LoggingType::DEBUG, "Entity \"" + std::to_string(entity) + "\""
            " signature set \"" + m_signatures[entity].to_string() + "\"");

        return m_signatures[entity];
    }

    /**
     * Sets the signature for a given entity.
     *
     * @param entity The ID of the entity to set the signature for.
     * @param component_type The signature to be set for the entity.
     * @return The signature of the entity.
     * @throw std::out_of_range if the entity ID is out of range.
     */
    Signature EntityManager::SetSignature(Entity entity, ComponentType component_type, bool value) {
        if (entity < 0 || entity >= MAX_ENTITIES) {
            std::out_of_range ex = std::out_of_range("Entity out of range.");
            LOG_CORE(LoggingType::ERROR, ex.what());
            throw ex;
        }

        // Set the signature for the given entity
        m_signatures[entity].set(component_type, value);

        LOG_CORE(LoggingType::DEBUG, "Entity \"" + std::to_string(entity) + "\""
            " signature set \"" + m_signatures[entity].to_string() + "\"");

        return m_signatures[entity];
    }

    /**
     * Retrieves the signature associated with a given entity.
     *
     * @param entity The ID of the entity to retrieve the signature for.
     * @return The signature associated with the given entity.
     * @throw std::out_of_range if the entity ID is out of range.
     */
    Signature EntityManager::GetSignature(Entity entity) {
        if (entity < 0 || entity >= MAX_ENTITIES) {
            std::out_of_range ex = std::out_of_range("Entity out of range.");
            LOG_CORE(LoggingType::ERROR, ex.what());
            throw ex;
        }

        return m_signatures[entity];
    }

    /**
     * @brief Checks if an entity has a specific component
     * 
     * @param entity Entity to check
     * @param component_type Component type ID
     * @return true 
     * @return false 
     */
    bool EntityManager::HasComponent(Entity entity, ComponentType component_type) {
        try {
            return GetSignature(entity).test(component_type);
        }
        catch(const std::exception& e) {
            return false;
        }
    }

    /**
     * @brief Number of living entities
     * 
     * @return Entity count
     */
    Entity EntityManager::EntityCount() const {
        return m_living_entity_count;
    }
}