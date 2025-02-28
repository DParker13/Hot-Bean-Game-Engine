/**
 * @file core_manager.cpp
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

#include "core_manager.hpp"

namespace Core {
    CoreManager::CoreManager() {
        _entityManager = std::make_unique<EntityManager>();
        _componentManager = std::make_unique<ComponentManager>();
        _systemManager = std::make_unique<SystemManager>();
    }
    
    CoreManager::~CoreManager() = default;

    /**
     * Creates a new entity and returns its unique identifier.
     *
     * @return The unique identifier of the newly created entity.
     *
     * @throws assertion failure if the maximum number of entities has been reached.
     */
    Entity CoreManager::CreateEntity() {
        return _entityManager->CreateEntity();
    }

    /**
     * Destroys an entity and releases its resources.
     *
     * @param entity The ID of the entity to destroy.
     *
     * @throws assertion failure if the entity ID is out of range or invalid.
     */
    void CoreManager::DestroyEntity(Entity entity) {
        _entityManager->DestroyEntity(entity);
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
    void CoreManager::RemoveAllComponents(Entity entity) {
        Signature signature = _entityManager->GetSignature(entity);

        for (int i = 0; i < signature.count(); i++) {
            if(signature[i]) {
                _componentManager->RemoveComponent(entity, i);
            }
        }
    }

    /**
     * Prints out the state of the ComponentManager for debugging purposes.
     */
    std::string CoreManager::ToString() const {
        std::stringstream str;
        str << _entityManager->ToString();
        str << _componentManager->ToString();
        str << _systemManager->ToString();

        return str.str();
    }
}