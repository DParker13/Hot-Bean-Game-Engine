/**
 * @file ecs_manager.h
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

#include <HotBeanEngine/application/managers/entity_manager.hpp>
#include <HotBeanEngine/application/managers/component_manager.hpp>
#include <HotBeanEngine/application/managers/system_manager.hpp>

namespace HBE::Application::Managers {
    using namespace HBE::Core;
    
    /**
     * @brief Cordinates between entity, component, and system managers.
     */
    class ECSManager {
    private:
        std::unique_ptr<EntityManager> m_entity_manager;
        std::unique_ptr<ComponentManager> m_component_manager;
        std::unique_ptr<SystemManager> m_system_manager;

    public:
        std::shared_ptr<LoggingManager> m_logging_manager;
        
        ECSManager(std::shared_ptr<LoggingManager> logging_manager);
        ~ECSManager() = default;

        EntityID CreateEntity();
        void DestroyEntity(EntityID entity);
        void DestroyAllEntities();
        void RemoveAllComponents(EntityID entity);
        std::vector<IComponent*> GetAllComponents(EntityID entity);
        EntityID EntityCount() const;
        std::vector<EntityID> GetAllEntities();

        /**
         * Registers a component type with the ComponentManager and assigns it a ComponentID id.
         *
         * @tparam T The type of component to be registered.
         * @return The ComponentID id associated with the given component type.
         * @throws assertion failure if the maximum number of component types has been reached.
         */
        template<typename T>
        ComponentID RegisterComponentID() {
            return m_component_manager->RegisterComponentID<T>();
        }

        /**
         * @brief Adds a component of type T to an entity. Registers the component type if it's not already registered.
         * 
         * @tparam T Component type
         * @param entity EntityID to add component to
         */
        template<typename T>
        void AddComponent(EntityID entity) {
            ComponentID component_id = m_component_manager->AddComponent<T>(entity);
            Signature signature = m_entity_manager->SetSignature(entity, component_id);
            m_system_manager->EntitySignatureChanged(entity, signature);
        }

        /**
         * @brief Adds a component of type T to an entity. Registers the component type if it's not already registered.
         * 
         * @tparam T Component type
         * @param entity EntityID to add component to
         * @param component Component to add
         */
        template<typename T>
        void AddComponent(EntityID entity, T component) {
            ComponentID component_id = m_component_manager->AddComponent<T>(entity, component);
            Signature signature = m_entity_manager->SetSignature(entity, component_id);
            m_system_manager->EntitySignatureChanged(entity, signature);
        }

        /**
         * Removes a component of type T from an entity.
         *
         * @param entity The ID of the entity to remove the component from.
         * @throws assertion failure if the entity ID is out of range.
         */
        template<typename T>
        void RemoveComponent(EntityID entity) {
            m_component_manager->RemoveComponent<T>(entity);
            Signature signature = m_entity_manager->SetSignature(entity, GetComponentID<T>());
            m_system_manager->EntitySignatureChanged(entity, signature);
        }

        /**
         * @brief Get the Component object
         * 
         * @tparam T The type of component
         * @param entity EntityID to get component from
         * @return T& Reference to the component
         */
        template<typename T>
        T& GetComponent(EntityID entity) {
            return m_component_manager->GetComponentData<T>(entity);
        }

        /**
         * @brief Get the Component Type id
         * 
         * @tparam T The type of component
         * @return ComponentID The ComponentID id
         */
        template<typename T>
        ComponentID GetComponentID() {
            return m_component_manager->GetComponentID<T>();
        }

        /**
         * @brief Checks if an entity has a component of a specific type
         * 
         * @tparam T Component type
         * @param entity EntityID to check
         * @return True if the entity has the component, false otherwise
         */
        template<typename T>
        bool HasComponent(EntityID entity) const {
            return m_component_manager->HasComponent<T>(entity);
        }

        /**
         * @brief Checks if an entity has a component of a specific type
         * 
         * @param entity EntityID to check
         * @param compoenent_name The name of the component
         * @return true 
         * @return false 
         */
        bool HasComponent(EntityID entity, std::string component_name) const;

        /**
         * @brief Checks if an entity has a component of a specific type
         * 
         * @param entity EntityID to check
         * @param component_id The type of the component
         * @return True if the entity has the component, false otherwise
         */
        bool HasComponent(EntityID entity, ComponentID component_id) const;

        /**
         * Retrieves the Component Name associated with the given component type.
         *
         * @param component_id The component type to retrieve the name for.
         * @return The name associated with the given component type, or an empty string if the component is not registered.
         */
        std::string GetComponentName(ComponentID component_id) const;

        /**
         * @brief Get the Component Type object
         * 
         * @param component_name The name of the component
         * @return ComponentID The ComponentID id
         */
        ComponentID GetComponentID(std::string component_name) const;

        /**
         * @brief Checks if a component is registered
         * 
         * @param component_id The type of the component
         * @return True if the component is registered
         */
        template<typename T>
        bool IsComponentRegistered() const {
            return m_component_manager->IsComponentRegistered<T>();
        };

        /**
         * @brief Checks if a component is registered
         * 
         * @param component_name The name of the component
         * @return True if the component is registered
         */
        bool IsComponentRegistered(std::string component_name) const;

        /**
         * @brief Checks if a component is registered
         * 
         * @param component_id The type of the component
         * @return True if the component is registered
         */
        bool IsComponentRegistered(ComponentID component_id) const;

        /**
         * @brief Registers a system to the ECS manager
         * 
         * @tparam T System type
         * @tparam Args Types of parameters
         * @param params System parameters
         * @return T& Reference to the registered system
         */
        template<typename T, typename... Args>
        T& RegisterSystem(Args&&... params) {
            T& system = m_system_manager->RegisterSystem<T, Args...>(std::forward<Args>(params)...);
            system.SetSignature();

            return system;
        }

        /**
         * @brief Registers a system to the ECS manager
         * 
         * @tparam T System type
         * @return T& Reference to the registered system
         */
        template<typename T>
        T& RegisterSystem() {
            T& system = m_system_manager->RegisterSystem<T>();
            system.SetSignature();

            return system;
        }

        /**
         * @brief Unregisters a system of type T
         * 
         * @tparam T The type of system to unregister
         */
        template<typename T>
        void UnregisterSystem() {
            m_system_manager->UnregisterSystem<T>();
        }

        void UnregisterSystem(ISystem* system);

        template<typename T>
        Signature& GetSignature() {
            return m_system_manager->GetSignature<T>();
        }

        const Signature& GetSignature(EntityID entity) const;

        template<typename T>
        bool IsSystemRegistered() {
            return m_system_manager->IsSystemRegistered<T>();
        }

        /**
         * @brief Get the System object
         * 
         * @tparam T The type of system
         * @return T* Pointer to the system
         */
        template<typename T>
        T* GetSystem() {
            return m_system_manager->GetSystem<T>();
        }

        /**
         * @brief Set the Signature of a System using Archetypes
         * 
         * @tparam S System type
         * @param archetype Archetype to set signature with
         */
        template<typename S>
        void SetSignature(IArchetype* archetype) {
            try {
                if (!IsSystemRegistered<S>()) {
                    LOG_CORE(LoggingType::WARNING, "System is not registered");
                    return;
                }

                Signature& signature = m_system_manager->GetSignature<S>();
                std::vector<std::string> component_names = archetype->GetComponentNames();

                for (std::string component_name : component_names) {
                    signature.set(GetComponentID(component_name));
                }
    
                m_system_manager->SetSignature<S>(signature);
            }
            catch(std::runtime_error& e) {
                LOG_CORE(LoggingType::ERROR, "Runtime error: Failed to set System signature");
            }
        }

        /**
         * @brief Set the Signature of a System using Components
         * 
         * @tparam S System type
         * @tparam Cs Component types
         */
        template<typename S, typename... Cs>
        void SetSignature() {
            try {
                Signature& signature = m_system_manager->GetSignature<S>();
                ((signature.set(IsComponentRegistered<Cs>() ?
                        GetComponentID<Cs>() :
                        RegisterComponentID<Cs>())), ...);
    
                m_system_manager->SetSignature<S>(signature);
            }
            catch(std::runtime_error&) {
                LOG_CORE(LoggingType::ERROR, "Runtime error: Failed to set System signature");
            }
        }

        /**
         * @brief Iterates over each system and calls specific game loop methods
         * 
         * @param state The game loop state
         */
        void IterateSystems(GameLoopState state);

        /**
         * @brief Iterates over each system and calls specific game loop event methods
         * 
         * @param event SDL event
         * @param state The game loop state
         */
        void IterateSystems(SDL_Event& event, GameLoopState state);
    
        /**
         * @brief Get all systems
         * @return std::vector<ISystem*> Vector of all systems
         */
        std::vector<ISystem*> GetAllSystems();
    };
}