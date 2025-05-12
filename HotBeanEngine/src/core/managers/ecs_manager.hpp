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

#include <memory>
#include <unordered_map>

#include "logging_manager.hpp"
#include "entity_manager.hpp"
#include "component_manager.hpp"
#include "system_manager.hpp"

using namespace Core::ECS;

namespace Core::Managers {
    // ECSManager combines EntityManager and ComponentManager to manage entities and components together in one system
    class ECSManager {
        private:
            std::shared_ptr<LoggingManager> _logging_manager;
            std::unique_ptr<EntityManager> _entityManager;
            std::unique_ptr<ComponentManager> _componentManager;
            std::unique_ptr<SystemManager> _systemManager;
        
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
                return _componentManager->RegisterComponentType<T>();
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
                ComponentType componentType = _componentManager->AddComponent<T>(entity, component);
                Signature signature = _entityManager->SetSignature(entity, componentType);
                _systemManager->EntitySignatureChanged(entity, signature);
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
                ComponentType componentType = _componentManager->RemoveComponent<T>(entity);
                Signature signature = _entityManager->SetSignature(entity, componentType);
                _systemManager->EntitySignatureChanged(entity, signature);
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
                return _componentManager->GetComponentData<T>(entity);
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
                return _componentManager->GetComponentType<T>();
            }

            /**
             * Retrieves the Component Name associated with the given component type.
             *
             * @param component_type The component type to retrieve the name for.
             *
             * @return The name associated with the given component type, or an empty string if the component is not registered.
             */
            std::string GetComponentName(ComponentType component_type) const;

            /**
             * @brief Get the registered Component Type using the Component Name
             * 
             * @param component_name Component Name to search
             * @return ComponentType
             * @return -1 if not found
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
    
            /**
             * Registers a system of type S with the ECSManager.
             *
             * @tparam T The type of system to be registered.
             *
             * @return A shared pointer to the registered system.
             *
             * @throws assertion failure if the system type has already been registered.
             */
            template<typename T>
            T& RegisterSystem(T* system) {
                return _systemManager->RegisterSystem<T>(system);
            }
    
            /**
             * Sets the signature for a system that has already been registered with the ECSManager.
             *
             * @tparam T The type of system for which to set the signature.
             * @param signature The new signature to be set for the system.
             *
             * This function delegates to the SystemManager to update the signature for the specified system type.
             */
            template<typename T>
            void SetSignature(Signature signature) {
                _systemManager->SetSignature<T>(signature);
            }
    
            template<typename S, typename... Cs>
            void SetSignature() {
                Signature& signature = _systemManager->GetSignature<S>();
    
                ((signature.set(GetComponentType<Cs>() == -1 ?
                    RegisterComponentType<Cs>() :
                    GetComponentType<Cs>())), ...);
    
                _systemManager->SetSignature<S>(signature);
            }
    
            /**
             * Retrieves a previously registered system by its type.
             *
             * @tparam T The type of system to be retrieved.
             *
             * @return A shared pointer to the system.
             *
             * @throws assertion failure if the system type has not been registered.
             */
            template<typename T>
            T* GetSystem() {
                return _systemManager->GetSystem<T>();
            }
    
            /**
             * Iterates over each system and calls its OnRender method.
             *
             * @param renderer The SDL_Renderer to render with.
             * @param window The SDL_Window that the renderer is attached to.
             * @param surface The SDL_Surface to render to.
             *
             * This function iterates over each system and calls its OnRender method, passing through the given renderer, window, and surface.
             */
            void IterateSystems(GameLoopState state) {
                _systemManager->IterateSystems(state);
            }
    
            /**
             * Iterates over each system and calls its OnEvent method.
             *
             * @param event The SDL_Event that contains the event data.
             *
             * This function iterates over each system and calls its OnEvent method, passing through the given event.
             */
            void IterateSystems(SDL_Event& event) {
                _systemManager->IterateSystems(event);
            }
    };
}