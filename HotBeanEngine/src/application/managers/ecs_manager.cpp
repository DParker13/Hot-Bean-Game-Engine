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
 */

#include <HotBeanEngine/application/managers/ecs_manager.hpp>

namespace HBE::Application::Managers {
    using namespace HBE::Core;
    ECSManager::ECSManager(std::shared_ptr<LoggingManager> logging_manager) : m_logging_manager(logging_manager) {
        m_entity_manager = std::make_unique<EntityManager>(logging_manager);
        m_component_manager = std::make_shared<ComponentManager>(logging_manager);
        m_system_manager = std::make_unique<SystemManager>(m_component_manager, logging_manager);
    }

    /**
     * Creates a new entity and returns its unique identifier.
     *
     * @return The unique identifier of the newly created entity.
     *
     * @throws assertion failure if the maximum number of entities has been reached.
     */
    EntityID ECSManager::CreateEntity() { return m_entity_manager->CreateEntity(); }

    /**
     * Destroys an entity and releases its resources.
     *
     * @param entity The ID of the entity to destroy.
     *
     * @throws assertion failure if the entity ID is out of range or invalid.
     */
    void ECSManager::DestroyEntity(EntityID entity) {
        m_entity_manager->DestroyEntity(entity);
        RemoveAllComponents(entity);
    }

    /**
     * @brief Destroys all entities and clears component/system mappings.
     */
    void ECSManager::DestroyAllEntities() { m_entity_manager->DestroyAllEntities(); }

    /**
     * @brief Retrieves all entity IDs in the manager.
     *
     * @return A vector of all active entity IDs.
     */
    std::vector<EntityID> ECSManager::GetAllEntities() { return m_entity_manager->GetAllEntities(); }

    /**
     * @brief Removes all components associated with a given entity.
     *
     * @param entity The ID of the entity from which all components are to be removed.
     *
     * This function retrieves the signature of the entity, which represents the
     * components attached to the entity. It iterates over each component type
     * indicated by the signature and removes the corresponding components from
     * the component manager.
     */
    void ECSManager::RemoveAllComponents(EntityID entity) {
        Signature signature = m_entity_manager->GetSignature(entity);

        for (size_t i = 0; i < signature.size(); i++) {
            if (signature[i]) {
                m_component_manager->RemoveComponent(entity, i);
            }
        }
    }

    std::vector<IComponent *> ECSManager::GetAllComponents(EntityID entity) {
        Signature signature = m_entity_manager->GetSignature(entity);
        std::vector<IComponent *> components = std::vector<IComponent *>();

        for (size_t i = 0; i < signature.size(); i++) {
            if (signature.test(i)) {
                components.push_back(m_component_manager->GetComponent(entity, (ComponentID)i));
            }
        }

        return components;
    }

    /**
     * @brief Gets the total number of active entities.
     *
     * @return The count of active entities.
     */
    EntityID ECSManager::EntityCount() const { return m_entity_manager->EntityCount(); }

    /**
     * @brief Unregisters a component type by name.
     *
     * @warning This will remove the component from all entities and update system signatures. This may lead to errors
     * or unintended behavior if systems expect the component to exist.
     * @param component_name The name of the component type to unregister.
     */
    void ECSManager::UnregisterComponentID(std::string component_name) {
        ComponentID component_id = GetComponentID(component_name);

        // Remove component from all entities that have it
        for (EntityID entity : GetAllEntities()) {
            if (HasComponent(entity, component_id)) {
                m_component_manager->RemoveComponent(entity, component_id);
            }
        }

        // Update all system signatures to remove this component
        for (ISystem *system : GetAllSystems()) {
            Signature system_signature = m_system_manager->GetSignature(system);
            if (system_signature[component_id]) {
                system_signature[component_id] = false;
            }
        }

        m_component_manager->UnregisterComponentID(component_name);
    }

    /**
     * @brief Checks if an entity has a specific component by name.
     *
     * @param entity The entity ID.
     * @param component_name The name of the component to check.
     * @return True if the entity has the component, false otherwise.
     */
    bool ECSManager::HasComponent(EntityID entity, std::string component_name) const {
        return m_entity_manager->HasComponent(entity, GetComponentID(component_name));
    }

    /**
     * @brief Checks if an entity has a specific component by ID.
     *
     * @param entity The entity ID.
     * @param component_id The component ID to check.
     * @return True if the entity has the component, false otherwise.
     */
    bool ECSManager::HasComponent(EntityID entity, ComponentID component_id) const {
        return m_entity_manager->HasComponent(entity, component_id);
    }

    /**
     * @brief Retrieves the component name associated with a component ID.
     *
     * @param component_id The component ID to look up.
     * @return The name associated with the given component ID, or an empty string if not registered.
     */
    std::string ECSManager::GetComponentName(ComponentID component_id) const {
        return m_component_manager->GetComponentName(component_id);
    }

    /**
     * @brief Get the registered Component Type using the Component Name
     *
     * @param component_name Component Name to search
     * @return ComponentID
     */
    ComponentID ECSManager::GetComponentID(std::string component_name) const {
        return m_component_manager->GetComponentID(component_name);
    }

    /**
     * @brief Checks if a component is registered
     *
     * @param component_name The name of the component
     * @return true if the component is registered, false otherwise
     */
    bool ECSManager::IsComponentRegistered(std::string component_name) const {
        return m_component_manager->IsComponentRegistered(component_name);
    }

    /**
     * @brief Checks if a component is registered
     *
     * @param component_id The type of the component
     * @return true if the component is registered, false otherwise
     */
    bool ECSManager::IsComponentRegistered(ComponentID component_id) const {
        return m_component_manager->IsComponentRegistered(component_id);
    }

    void ECSManager::UnregisterSystem(ISystem *system) { m_system_manager->UnregisterSystem(system); }

    /**
     * @brief Gets the component signature for an entity.
     *
     * @param entity The entity ID.
     * @return A reference to the entity's component signature.
     */
    const Signature &ECSManager::GetSignature(EntityID entity) const { return m_entity_manager->GetSignature(entity); }

    void ECSManager::RegisterComponentListener(ComponentListener *listener) {
        if (listener) {
            m_component_listeners.push_back(listener);
        }
    }

    /**
     * @brief Loop through all systems
     *
     * @param state Game loop state
     */
    void ECSManager::IterateSystems(GameLoopState state) { m_system_manager->IterateSystems(state); }

    /**
     * @brief Loop through all systems
     *
     * @param event SDL event
     * @param state Game loop state
     */
    void ECSManager::IterateSystems(SDL_Event &event, GameLoopState state) {
        m_system_manager->IterateSystems(event, state);
    }

    std::vector<ISystem *> ECSManager::GetAllSystems() { return m_system_manager->GetAllSystems(); }
} // namespace HBE::Application::Managers