/**
 * @file entity_manager.hpp
 * @author Daniel Parker (DParker13)
 * @brief Manages the creation and destruction of entities.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once

#include <queue>

#include "../managers/logging_manager.hpp"

using namespace HBE::Core;
using namespace Config;

namespace HBE::Managers {
    // EntityManager manages the creation and destruction of entities
    class EntityManager {
        public:
            EntityManager(std::shared_ptr<LoggingManager> logging_manager);
            ~EntityManager();

            Entity CreateEntity();
            void DestroyEntity(Entity entity);
            Signature SetSignature(Entity entity, ComponentType component_type);
            Signature SetSignature(Entity entity, ComponentType component_type, bool value);
            Signature GetSignature(Entity entity);
            bool HasComponent(Entity entity, ComponentType component_type);
            Entity EntityCount() const;
            
        private:
            void InitializeEntityQueue();

        private:
            // Logging manager
            std::shared_ptr<LoggingManager> m_logging_manager;

            // Queue of unused entity IDs
            std::queue<Entity> m_available_entities;

            std::unordered_map<Entity, bool> m_alive_entities;

            // Array of signatures where the index corresponds to the entity ID
            std::array<Signature, MAX_ENTITIES> m_signatures;

            // Total living entities - used to keep limits on how many exist
            Entity m_living_entity_count = 0;
    };
}