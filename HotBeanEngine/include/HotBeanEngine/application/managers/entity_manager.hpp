/**
 * @file entity_manager.hpp
 * @author Daniel Parker (DParker13)
 * @brief Manages the creation and destruction of entities.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <queue>

#include <HotBeanEngine/application/managers/logging_manager.hpp>

namespace HBE::Application::Managers {
    using namespace HBE::Core;

    /**
     * @brief Manages entity creation and destruction lifecycle.
     * Handles entity ID allocation, recycling, and signature management.
     * Maintains entity validity and component associations.
     */
    class EntityManager {
    private:
        // Logging manager
        std::shared_ptr<LoggingManager> m_logging_manager;

        // Queue of unused entity IDs
        std::queue<EntityID> m_available_entities;

        std::unordered_map<EntityID, bool> m_alive_entities;

        // Array of signatures where the index corresponds to the entity ID
        std::array<Signature, MAX_ENTITIES> m_signatures;

        // Total living entities - used to keep limits on how many exist
        EntityID m_living_entity_count = 0;
        
    public:
        EntityManager(std::shared_ptr<LoggingManager> logging_manager);
        ~EntityManager();

        EntityID CreateEntity();
        void DestroyEntity(EntityID entity);
        Signature SetSignature(EntityID entity, ComponentID component_id);
        Signature SetSignature(EntityID entity, ComponentID component_id, bool value);
        Signature GetSignature(EntityID entity);
        bool HasComponent(EntityID entity, ComponentID component_id);
        EntityID EntityCount() const;
        
    private:
        void InitializeEntityQueue();
    };
}