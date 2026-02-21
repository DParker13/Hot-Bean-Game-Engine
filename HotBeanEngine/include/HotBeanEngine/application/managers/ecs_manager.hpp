/**
 * @file ecs_manager.hpp
 * @author Daniel Parker
 * @brief Manages all ECS managers (entities, components, and systems).
 *
 * @details Merges EntityManager, ComponentManager, and SystemManager into one
 * class for easier management of entities, components, and systems. A singleton is created in Application.cpp to handle
 * all entities, components, and systems in the game. This class handles all the backend management of the ECS framework
 * and has been further expanded by gameobject classes that act as a single class. Gameobjects follow the ECS framework
 * but are able to be manipulated by the user directly without a system.
 * @version 0.1
 * @date 2025-02-18
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <HotBeanEngine/application/managers/component_listener.hpp>
#include <HotBeanEngine/application/managers/component_manager.hpp>
#include <HotBeanEngine/application/managers/entity_manager.hpp>
#include <HotBeanEngine/application/managers/system_manager.hpp>

namespace HBE::Application::Managers {
    using HBE::Core::ComponentID;
    using HBE::Core::EntityID;
    using HBE::Core::IArchetype;
    using HBE::Core::Signature;

    /**
     * @brief Coordinates between entity, component, and system managers.
     */
    class ECSManager {
    private:
        std::unique_ptr<EntityManager> m_entity_manager;
        std::shared_ptr<ComponentManager> m_component_manager;
        std::unique_ptr<SystemManager> m_system_manager;
        std::vector<ComponentListener *> m_component_listeners;

    public:
        std::shared_ptr<LoggingManager> m_logging_manager;

        // ============================================================================
        // Constructor / Destructor
        // ============================================================================

        ECSManager(std::shared_ptr<LoggingManager> logging_manager);
        ~ECSManager() = default;

        // ============================================================================
        // Entity Management
        // ============================================================================

        EntityID CreateEntity();
        void DestroyEntity(EntityID entity);
        void DestroyAllEntities();
        EntityID EntityCount() const;
        std::vector<EntityID> GetAllEntities();

        // ============================================================================
        // Component Management - Registration
        // ============================================================================

        template <typename T>
        ComponentID RegisterComponentID() {
            return m_component_manager->RegisterComponentID<T>();
        }

        template <typename T>
        void UnregisterComponentID() {
            m_component_manager->UnregisterComponentID<T>();
        }

        void UnregisterComponentID(std::string component_name);

        template <typename T>
        bool IsComponentRegistered() const {
            return m_component_manager->IsComponentRegistered<T>();
        }

        bool IsComponentRegistered(std::string component_name) const;
        bool IsComponentRegistered(ComponentID component_id) const;

        // ============================================================================
        // Component Management - Add / Remove / Access
        // ============================================================================

        /**
         * @brief Adds a component of type T to an entity. Registers if not already registered.
         * @tparam T Component type
         * @param entity EntityID to add component to
         */
        template <typename T>
        void AddComponent(EntityID entity) {
            ComponentID component_id = m_component_manager->AddComponent<T>(entity);
            Signature signature = m_entity_manager->SetSignature(entity, component_id);
            m_system_manager->EntitySignatureChanged(entity, signature);
            NotifyComponentAdded(component_id, entity);
        }

        /**
         * @brief Adds a component of type T to an entity. Registers if not already registered.
         * @tparam T Component type
         * @param entity EntityID to add component to
         * @param component Component to add
         */
        template <typename T>
        void AddComponent(EntityID entity, T component) {
            ComponentID component_id = m_component_manager->AddComponent<T>(entity, component);
            Signature signature = m_entity_manager->SetSignature(entity, component_id);
            m_system_manager->EntitySignatureChanged(entity, signature);
            NotifyComponentAdded(component_id, entity);
        }

        /**
         * @brief Removes a component of type T from an entity.
         * @tparam T Component type
         * @param entity EntityID to remove component from
         */
        template <typename T>
        void RemoveComponent(EntityID entity) {
            m_component_manager->RemoveComponent<T>(entity);
            Signature signature = m_entity_manager->SetSignature(entity, GetComponentID<T>());
            m_system_manager->EntitySignatureChanged(entity, signature);
            NotifyComponentRemoved(entity);
        }

        void RemoveAllComponents(EntityID entity);

        /**
         * @brief Get the Component object
         * @tparam T The type of component
         * @param entity EntityID to get component from
         * @return T& Reference to the component
         */
        template <typename T>
        T &GetComponent(EntityID entity) {
            return m_component_manager->GetComponentData<T>(entity);
        }

        std::vector<IComponent *> GetAllComponents(EntityID entity);

        // ============================================================================
        // Component Management - Query / Lookup
        // ============================================================================

        /**
         * @brief Get all Entities that have all specified component types.
         * @warning USE THIS SPARINGLY! Use Systems instead for better performance.
         * @tparam Components
         * @return std::set<EntityID>
         */
        template <typename... Components>
        std::set<EntityID> GetEntitiesWithComponents() {
            std::set<EntityID> result;
            for (EntityID entity : GetAllEntities()) {
                if ((HasComponent<Components>(entity) && ...)) {
                    result.insert(entity);
                }
            }
            return result;
        }

        /**
         * @brief Checks if an entity has a component of a specific type
         * @tparam T Component type
         * @param entity EntityID to check
         * @return True if the entity has the component, false otherwise
         */
        template <typename T>
        bool HasComponent(EntityID entity) const {
            return m_component_manager->HasComponent<T>(entity);
        }

        bool HasComponent(EntityID entity, std::string component_name) const;
        bool HasComponent(EntityID entity, ComponentID component_id) const;

        /**
         * @brief Get the Component Type id
         * @tparam T The type of component
         * @return ComponentID The ComponentID id
         */
        template <typename T>
        ComponentID GetComponentID() {
            return m_component_manager->GetComponentID<T>();
        }

        ComponentID GetComponentID(std::string component_name) const;
        std::string GetComponentName(ComponentID component_id) const;

        // ============================================================================
        // System Management - Registration / Unregistration
        // ============================================================================

        /**
         * @brief Registers a system to the ECS manager
         * @tparam T System type
         * @tparam Args Types of parameters
         * @param params System parameters
         * @return T& Reference to the registered system
         */
        template <typename T, typename... Args>
        T &RegisterSystem(Args &&...params) {
            T &system = m_system_manager->RegisterSystem<T, Args...>(std::forward<Args>(params)...);
            system.SetSignature();
            return system;
        }

        /**
         * @brief Registers a system to the ECS manager
         * @tparam T System type
         * @return T& Reference to the registered system
         */
        template <typename T>
        T &RegisterSystem() {
            T &system = m_system_manager->RegisterSystem<T>();
            system.SetSignature();
            return system;
        }

        /**
         * @brief Unregisters a system of type T
         * @tparam T The type of system to unregister
         */
        template <typename T>
        void UnregisterSystem() {
            m_system_manager->UnregisterSystem<T>();
        }

        void UnregisterSystem(ISystem *system);

        template <typename T>
        bool IsSystemRegistered() {
            return m_system_manager->IsSystemRegistered<T>();
        }

        // ============================================================================
        // System Management - Signature / Access
        // ============================================================================

        /**
         * @brief Get the System object
         * @tparam T The type of system
         * @return T* Pointer to the system
         */
        template <typename T>
        T *GetSystem() {
            return m_system_manager->GetSystem<T>();
        }

        template <typename T>
        Signature &GetSignature() {
            return m_system_manager->GetSignature<T>();
        }

        const Signature &GetSignature(EntityID entity) const;

        /**
         * @brief Set the Signature of a System using Archetypes
         * @tparam S System type
         * @param archetype Archetype to set signature with
         */
        template <typename S>
        void SetSignature(IArchetype *archetype) {
            try {
                if (!IsSystemRegistered<S>()) {
                    LOG_CORE(LoggingType::WARNING, "System is not registered");
                    return;
                }

                Signature &signature = m_system_manager->GetSignature<S>();
                std::vector<std::string> component_names = archetype->GetComponentNames();

                for (std::string component_name : component_names) {
                    signature.set(GetComponentID(component_name));
                }

                m_system_manager->SetSignature<S>(signature);
            } catch (std::runtime_error &e) {
                LOG_CORE(LoggingType::ERROR, "Runtime error: Failed to set System signature");
            }
        }

        /**
         * @brief Set the Signature of a System using Components
         * @tparam S System type
         * @tparam Cs Component types
         */
        template <typename S, typename... Cs>
        void SetSignature() {
            try {
                Signature &signature = m_system_manager->GetSignature<S>();
                ((signature.set(IsComponentRegistered<Cs>() ? GetComponentID<Cs>() : RegisterComponentID<Cs>())), ...);

                m_system_manager->SetSignature<S>(signature);
            } catch (std::runtime_error &) {
                LOG_CORE(LoggingType::ERROR, "Runtime error: Failed to set System signature");
            }
        }

        std::vector<ISystem *> GetAllSystems();

        // ============================================================================
        // Game Loop / Iteration
        // ============================================================================

        /**
         * @brief Iterates over each system and calls specific game loop methods
         * @param state The game loop state
         */
        void IterateSystems(GameLoopState state);

        /**
         * @brief Iterates over each system and calls specific game loop event methods
         * @param event SDL event
         * @param state The game loop state
         */
        void IterateSystems(SDL_Event &event, GameLoopState state);

        // ============================================================================
        // Component Listeners
        // ============================================================================

        /**
         * @brief Register a listener to receive component change notifications.
         * @param listener The listener to register.
         */
        void RegisterComponentListener(ComponentListener *listener);

        /**
         * @brief Notify all listeners that a component was added to an entity.
         * @param entity The entity ID that was added.
         */
        void NotifyComponentAdded(ComponentID component_id, EntityID entity) {
            for (ComponentListener *listener : m_component_listeners) {
                const auto &listened_components = listener->GetListenedComponents();
                if (listened_components.count(component_id)) {
                    // Check if entity now has all components the listener is interested in
                    bool has_all_components = true;
                    for (ComponentID id : listened_components) {
                        if (!HasComponent(entity, id)) {
                            has_all_components = false;
                            break;
                        }
                    }
                    if (has_all_components) {
                        listener->OnComponentAdded(m_component_manager->GetComponent(entity, component_id), entity);
                    }
                }
            }
        }

        /**
         * @brief Notify all listeners that a component was removed from an entity.
         * @param entity The entity ID that was removed.
         */
        void NotifyComponentRemoved(EntityID entity) {
            for (ComponentListener *listener : m_component_listeners) {
                const auto &listened_components = listener->GetListenedComponents();
                // Check if entity still has all components the listener is interested in
                bool has_all_components = true;
                for (ComponentID id : listened_components) {
                    if (!HasComponent(entity, id)) {
                        has_all_components = false;
                        break;
                    }
                }
                // Only notify if entity no longer has all required components
                if (!has_all_components) {
                    listener->OnComponentRemoved(entity);
                }
            }
        }
    };
} // namespace HBE::Application::Managers