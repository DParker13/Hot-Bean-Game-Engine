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
    ECSManager::ECSManager(std::shared_ptr<LoggingManager> logging_manager) : m_logging_manager(logging_manager) {
        m_entity_manager = std::make_unique<EntityManager>(logging_manager);
        m_component_manager = std::make_unique<ComponentManager>(logging_manager);
        m_system_manager = std::make_unique<SystemManager>(logging_manager);
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

    void ECSManager::DestroyAllEntities() {
        // for (EntityID entity : GetAllEntities()) {
        //     RemoveAllComponents(entity);
        // }

        // Clear all component data to ensure clean state for next scene
        m_component_manager->ClearAllComponents();
        m_entity_manager->DestroyAllEntities();
    }

    std::vector<EntityID> ECSManager::GetAllEntities() { return m_entity_manager->GetAllEntities(); }

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

    EntityID ECSManager::EntityCount() const { return m_entity_manager->EntityCount(); }

    bool ECSManager::HasComponent(EntityID entity, std::string component_name) const {
        return m_entity_manager->HasComponent(entity, GetComponentID(component_name));
    }

    bool ECSManager::HasComponent(EntityID entity, ComponentID component_id) const {
        return m_entity_manager->HasComponent(entity, component_id);
    }

    /**
     * Retrieves the Component Name associated with the given component type.
     *
     * @param component_id The component type to retrieve the name for.
     * @return The name associated with the given component type, or an empty string if the component is not registered.
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

    const Signature &ECSManager::GetSignature(EntityID entity) const { return m_entity_manager->GetSignature(entity); }

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