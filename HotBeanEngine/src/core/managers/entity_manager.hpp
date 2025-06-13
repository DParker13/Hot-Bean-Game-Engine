/**
 * @file entity_manager.h
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

#include "../ecs/all_ecs.hpp"
#include "../managers/logging_manager.hpp"

using namespace Core::ECS;
using namespace Config;

namespace Core::Managers {
    // EntityManager manages the creation and destruction of entities
    class EntityManager {
        public:
            EntityManager(std::shared_ptr<LoggingManager> logging_manager);
            EntityManager();
            ~EntityManager();

            Entity CreateEntity();
            void DestroyEntity(Entity entity);
            Signature SetSignature(Entity entity, ComponentType component_type);
            Signature GetSignature(Entity entity);
            bool HasComponent(Entity entity, ComponentType component_type);
            Entity EntityCount() const;

        private:
            // Logging manager
            std::shared_ptr<LoggingManager> m_logging_manager;

            // Queue of unused entity IDs
            std::queue<Entity> m_available_entities{};

            // Array of signatures where the index corresponds to the entity ID
            std::array<Signature, MAX_ENTITIES> m_signatures{};

            // Total living entities - used to keep limits on how many exist
            Entity m_living_entity_count = 0;

            bool m_testing = false;

            void InitializeEntityQueue();
    };
}