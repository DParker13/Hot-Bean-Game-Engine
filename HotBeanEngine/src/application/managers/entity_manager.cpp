/**
 * @file entity_manager.cpp
 * @author Daniel Parker (DParker13)
 * @brief Manages the creation and destruction of entities.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 */

#include <HotBeanEngine/application/managers/entity_manager.hpp>

namespace HBE::Application::Managers {
    /**
     * Constructs an EntityManager and initializes the queue of available entity IDs.
     * 
     * This constructor fills the queue with all possible entity IDs, making them 
     * available for future use. The entity IDs range from 0 to MAX_ENTITIES - 1.
     */
    EntityManager::EntityManager(std::shared_ptr<LoggingManager> logging_manager)
        : m_logging_manager(logging_manager) {

        LOG_CORE(LoggingType::DEBUG, "Initializing EntityManager");

        InitializeEntities();

        LOG_CORE(LoggingType::INFO, "Initialized " + std::to_string(m_available_entities.size()) + " Entities (starting at 0)");
    }

    EntityManager::~EntityManager() = default;

    /**
     * @brief Initializes the queue with available entity IDs.
     * 
     * Fills the queue with all possible entity IDs, making them 
     * available for future use. The entity IDs range from 0 to MAX_ENTITIES - 1.
     */
    void EntityManager::InitializeEntities() {
        m_living_entity_count = 0;

        // Clear existing queue
        while (!m_available_entities.empty()) {
            m_available_entities.pop();
        }

        for (EntityID entity_id = 0; entity_id < MAX_ENTITIES; entity_id++) {
            m_available_entities.push(entity_id);
            m_alive_entities[entity_id] = false;
            m_signatures[entity_id].reset();
        }
    }

    /**
     * @brief Creates a new entity and returns its unique identifier.
     *
     * @return The unique identifier of the newly created entity.
     * @throw std::overflow_error if the maximum number of entities has been reached.
     */
    EntityID EntityManager::CreateEntity() {
        if (m_living_entity_count >= MAX_ENTITIES) {
            LOG_CORE(LoggingType::WARNING, "Maximum number of entities reached.");
            return MAX_ENTITIES;
        }

        // Take an ID from the front of the queue
        EntityID id = m_available_entities.front();
        m_alive_entities[id] = true;

        LOG_CORE(LoggingType::DEBUG, "Creating EntityID \"" + std::to_string(id) + "\"");

        m_available_entities.pop();
        m_living_entity_count++;

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
    void EntityManager::DestroyEntity(EntityID entity) {
        if (entity < 0 || entity >= MAX_ENTITIES) {
            LOG_CORE(LoggingType::ERROR, "Entity out of range.");
            return;
        }

        // If the entity is not alive, return
        if (!m_alive_entities[entity]) return;

        LOG_CORE(LoggingType::DEBUG, "Destroying EntityID \"" + std::to_string(entity) + "\"");

        // Invalidate the destroyed entity's signature
        m_signatures[entity].reset();

        // Place the destroyed entity ID at the back of the queue
        m_available_entities.push(entity);
        m_alive_entities[entity] = false;
        m_living_entity_count--;

        LOG_CORE(LoggingType::INFO, "Entity \"" + std::to_string(entity) + "\" destroyed.");
        LOG_CORE(LoggingType::DEBUG, "\tLiving Entities: " + std::to_string(m_living_entity_count));
        LOG_CORE(LoggingType::DEBUG, "\tAvailable Entities: " + std::to_string(m_available_entities.size()));
    }

    void EntityManager::DestroyAllEntities() {
        LOG_CORE(LoggingType::DEBUG, "Destroying all entities.");

        // Re-initialize the entity queue
        InitializeEntities();

        LOG_CORE(LoggingType::INFO, "All entities destroyed.");
        LOG_CORE(LoggingType::DEBUG, "\tLiving Entities: " + std::to_string(m_living_entity_count));
        LOG_CORE(LoggingType::DEBUG, "\tAvailable Entities: " + std::to_string(m_available_entities.size()));
    }

    /**
     * Sets the signature for a given entity.
     *
     * @param entity The ID of the entity to set the signature for.
     * @param component_id The signature to be set for the entity.
     * @return The signature of the entity.
     * @throw std::out_of_range if the entity ID is out of range.
     */
    Signature EntityManager::SetSignature(EntityID entity, ComponentID component_id) {
        if (entity < 0 || entity >= MAX_ENTITIES) {
            std::out_of_range ex = std::out_of_range("Entity out of range.");
            LOG_CORE(LoggingType::ERROR, ex.what());
            throw ex;
        }

        // Set the signature for the given entity
        m_signatures[entity].set(component_id);

        LOG_CORE(LoggingType::DEBUG, "Entity \"" + std::to_string(entity) + "\""
            " signature set \"" + m_signatures[entity].to_string() + "\"");

        return m_signatures[entity];
    }

    /**
     * Sets the signature for a given entity.
     *
     * @param entity The ID of the entity to set the signature for.
     * @param component_id The signature to be set for the entity.
     * @return The signature of the entity.
     * @throw std::out_of_range if the entity ID is out of range.
     */
    Signature EntityManager::SetSignature(EntityID entity, ComponentID component_id, bool value) {
        if (entity < 0 || entity >= MAX_ENTITIES) {
            std::out_of_range ex = std::out_of_range("Entity out of range.");
            LOG_CORE(LoggingType::ERROR, ex.what());
            throw ex;
        }

        // Set the signature for the given entity
        m_signatures[entity].set(component_id, value);

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
    Signature EntityManager::GetSignature(EntityID entity) {
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
     * @param entity EntityID to check
     * @param component_id Component type ID
     * @return true 
     * @return false 
     */
    bool EntityManager::HasComponent(EntityID entity, ComponentID component_id) {
        try {
            return GetSignature(entity).test(component_id);
        }
        catch(const std::exception&) {
            return false;
        }
    }

    /**
     * @brief Number of living entities
     * 
     * @return EntityID count
     */
    EntityID EntityManager::EntityCount() const {
        return m_living_entity_count;
    }

    std::vector<EntityID> EntityManager::GetAllEntities() {
        std::vector<EntityID> entities;
        entities.reserve(m_living_entity_count);

        size_t count = 0;
        for (EntityID entity_id = 0; entity_id < MAX_ENTITIES; entity_id++) {
            if (m_alive_entities[entity_id]) {
                entities.push_back(entity_id);
                count++;
            }

            if (count == m_living_entity_count) {
                break;
            }
        }

        return entities;
    }
}