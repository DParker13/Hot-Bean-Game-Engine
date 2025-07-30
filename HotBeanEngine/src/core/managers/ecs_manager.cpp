/**
 * @file ecs_manager.cpp
 * @author Daniel Parker (DParker13)
 * @brief Manages all ECS managers (entities, components, and systems).
 * 
 * @details Merges EntityManager, ComponentManager, and SystemManager into one 
 * class for easier management of entities, components, and systems. A singleton is created in Application.cpp to handle
 * all entities, components, and systems in the game. This class handles all the backend management of the ECS framework
 * and has been further expanded by gameobject classes that act as a single class. Gameobjects follow the ECS framework
 * but are able to be manipulated by the user directly without a system.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "ecs_manager.hpp"

namespace Core::Managers {
    ECSManager::ECSManager(std::shared_ptr<LoggingManager> logging_manager)
        : m_logging_manager(logging_manager) {
        m_entity_manager = std::make_unique<EntityManager>(logging_manager);
        m_component_manager = std::make_unique<ComponentManager>(logging_manager);
        m_system_manager = std::make_unique<SystemManager>(logging_manager);
    }

    /**
     * Destroys an entity and releases its resources.
     *
     * @param entity The ID of the entity to destroy.
     *
     * @throws assertion failure if the entity ID is out of range or invalid.
     */
    void ECSManager::DestroyEntity(Entity entity) {
        m_entity_manager->DestroyEntity(entity);
        RemoveAllComponents(entity);
    }

    /**
     * Removes all components associated with a given entity.
     *
     * @param entity The ID of the entity from which all components are to be removed.
     *
     * This function retrieves the signature of the entity, which represents the
     * components attached to the entity. It iterates over each component type
     * indicated by the signature and removes the corresponding components from
     * the component manager.
     */
    void ECSManager::RemoveAllComponents(Entity entity) {
        Signature signature = m_entity_manager->GetSignature(entity);

        for (int i = 0; i < signature.count(); i++) {
            if(signature[i]) {
                m_component_manager->RemoveComponent(entity, i);
            }
        }
    }

    std::vector<Component*> ECSManager::GetAllComponents(Entity entity) {
        Signature signature = m_entity_manager->GetSignature(entity);

        std::vector<Component*> components = std::vector<Component*>();

        size_t index = signature._Find_first();
        while (index < signature.size()) {
            if(signature[index]) {
                components.push_back(&m_component_manager->GetComponent(entity, index));
            }

            // Find the next 1
            index = signature._Find_next(index);
        }

        return components;
    }
}