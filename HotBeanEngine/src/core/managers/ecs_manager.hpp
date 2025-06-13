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
 * 
 */

#pragma once

#include "logging_manager.hpp"
#include "entity_manager.hpp"
#include "component_manager.hpp"
#include "system_manager.hpp"

using namespace Core::ECS;

namespace Core::Managers {
    // ECSManager combines EntityManager and ComponentManager to manage entities and components together in one system
    class ECSManager {
        private:
            std::shared_ptr<LoggingManager> m_logging_manager;
            std::unique_ptr<EntityManager> m_entity_manager;
            std::unique_ptr<ComponentManager> m_component_manager;
            std::unique_ptr<SystemManager> m_system_manager;
        
        public:
            ECSManager(std::shared_ptr<LoggingManager> logging_manager);
            ~ECSManager() = default;
    
            Entity CreateEntity();
            void DestroyEntity(Entity entity);
            void RemoveAllComponents(Entity entity);
            std::vector<Component*> GetAllComponents(Entity entity);
            Entity EntityCount() const;
    
            /**
             * Registers a component type with the ComponentManager and assigns it a ComponentType id.
             *
             * @tparam T The type of component to be registered.
             *
             * @return The ComponentType id associated with the given component type.
             *
             * @throws assertion failure if the maximum number of component types has been reached.
             */
            template<typename T>
            ComponentType RegisterComponentType() {
                return m_component_manager->RegisterComponentType<T>();
            }
    
            /**
             * Adds a component to an entity.
             *
             * @param entity The ID of the entity to add the component to.
             * @param component The component to add.
             *
             * @throws assertion failure if the entity ID is out of range.
             */
            template<typename T>
            void AddComponent(Entity entity, T component) {
                ComponentType component_type = m_component_manager->AddComponent<T>(entity, component);
                Signature signature = m_entity_manager->SetSignature(entity, component_type);
                m_system_manager->EntitySignatureChanged(entity, signature);
            }
    
            /**
             * Removes a component of type T from an entity.
             *
             * @param entity The ID of the entity to remove the component from.
             *
             * @throws assertion failure if the entity ID is out of range.
             */
            template<typename T>
            void RemoveComponent(Entity entity) {
                ComponentType component_type = m_component_manager->RemoveComponent<T>(entity);
                Signature signature = m_entity_manager->SetSignature(entity, component_type);
                m_system_manager->EntitySignatureChanged(entity, signature);
            }
    
            /**
             * Retrieves a component of type T associated with a given entity.
             *
             * @param entity The ID of the entity to retrieve the component for.
             *
             * @return A shared pointer to the component of type T.
             *
             * @throws assertion failure if the component type is not registered.
             */
            template<typename T>
            T& GetComponent(Entity entity) {
                return m_component_manager->GetComponentData<T>(entity);
            }
    
            /**
             * Retrieves the ComponentType id associated with a given component type.
             *
             * @tparam T The type of component to retrieve the ComponentType id for.
             *
             * @return The ComponentType id associated with the given component type.
             *
             * @throws assertion failure if the component type is not registered.
             */
            template<typename T>
            ComponentType GetComponentType() {
                return m_component_manager->GetComponentType<T>();
            }

            /**
             * @brief Checks if an entity has a component of a specific type
             * 
             * @tparam T Component type
             * @param entity Entity to check
             * @return true 
             * @return false 
             */
            template<typename T>
            bool HasComponent(Entity entity) const {
                return m_entity_manager->HasComponent(entity, m_component_manager->GetComponentType<T>());
            }

            /**
             * @brief Checks if an entity has a component of a specific type
             * 
             * @param entity Entity to check
             * @param compoenent_name The name of the component
             * @return true 
             * @return false 
             */
            bool HasComponent(Entity entity, std::string component_name) const;

            /**
             * Retrieves the Component Name associated with the given component type.
             *
             * @param component_type The component type to retrieve the name for.
             *
             * @return The name associated with the given component type, or an empty string if the component is not registered.
             */
            std::string GetComponentName(ComponentType component_type) const;

            /**
             * @brief Get the Component Type object
             * 
             * @param component_name The name of the component
             * @return ComponentType 
             */
            ComponentType GetComponentType(std::string component_name) const;

            /**
             * @brief Checks if a component is registered
             * 
             * @param component_name The name of the component
             * @return true 
             * @return false 
             */
            bool IsComponentRegistered(std::string component_name) const;

            /**
             * @brief Checks if a component is registered
             * 
             * @param component_type The type of the component
             * @return true 
             * @return false 
             */
            bool IsComponentRegistered(ComponentType component_type) const;

            template<typename T, typename... Args>
            T& RegisterSystem(Args&&... params) {
                T& system = m_system_manager->RegisterSystem<T, Args...>(std::forward<Args>(params)...);
                system.SetSignature();

                return system;
            }

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

            template<typename S, typename... Cs>
            void SetSignature() {
                Signature& signature = m_system_manager->GetSignature<S>();
    
                ((signature.set(GetComponentType<Cs>() == -1 ?
                    RegisterComponentType<Cs>() :
                    GetComponentType<Cs>())), ...);
    
                m_system_manager->SetSignature<S>(signature);
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
    };
}