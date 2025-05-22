/**
 * @file component_manager.h
 * @author Daniel Parker (DParker13)
 * @brief Manages the entity-component relationship.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include <unordered_map>
#include <memory>

#include "../ecs/all_ecs.hpp"
#include "../managers/logging_manager.hpp"

using namespace Core::ECS;

namespace Core::Managers {
    // ComponentManager manages the creation and destruction of components for entities
    class ComponentManager {
        public:
            ComponentManager(std::shared_ptr<LoggingManager> logging_manager);
            ~ComponentManager();
    
            void RemoveComponent(Entity entity, ComponentType component_type);
            Component& GetComponent(Entity entity, ComponentType component_type);

            /**
             * Registers a component type with the ComponentManager and assigns it a ComponentType id.
             *
             * @param typeName The name of the component type to be registered as a string.
             *
             * @throws assertion failure if the maximum number of component types has been reached.
             */
            template<typename T>
            ComponentType RegisterComponentType() {
                static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component!");
                assert(m_registered_components < MAX_COMPONENTS && "Reached maximum number of component!");

                T component;
                std::string component_name = component.GetName();
                assert(!component_name.empty() && "Component name not set!");

                m_logging_manager->Log(LoggingType::DEBUG, "Registering Component \"" + component_name + "\"");
    
                ComponentType component_type = m_registered_components;

                m_logging_manager->Log(LoggingType::DEBUG, "\tComponentType \"" + std::to_string(component_type) + "\"");
    
                // Maps ComponentType id to Component Object Type name
                m_component_type_to_name[component_type] = component_name;
    
                // Maps ComponentType to an id
                m_component_name_to_type[component_name] = component_type;
    
                // Create new sparse set for component data
                m_component_name_to_data[component_name] = std::make_shared<SparseSet<T, MAX_ENTITIES>>();
    
                m_registered_components++;

                m_logging_manager->Log(LoggingType::DEBUG, "\t" + std::to_string(m_registered_components) + " Registered Components");
    
                return component_type;
            }
    
            /*
            When you add a component to an entity, check if the component is registered.
            If a component is not registered, a component array must be created.
            This array keeps track of the entities that have that component.
            This function creates a unique signature for all the components.
            */
            template<typename T>
            ComponentType AddComponent(Entity entity, T& componentData) {
                static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component!");
                assert(!componentData.GetName().empty() && "Component name not set!");

                m_logging_manager->Log(LoggingType::DEBUG, "Adding Component \"" + componentData.GetName() + "\" to"
                    " Entity \"" + std::to_string(entity) + "\"");
    
                // Register component type if it's not already registered
                if (m_component_name_to_type.find(componentData.GetName()) == m_component_name_to_type.end()) {
                    m_logging_manager->Log(LoggingType::DEBUG, "\tComponent \"" + componentData.GetName() + "\" not registered... Attempting to Register");
                    RegisterComponentType<T>();
                }
    
                GetComponentSet<T>()->Insert(entity, componentData);
                return m_component_name_to_type[componentData.GetName()];
            }
    
            
            /**
             * Removes a component of type T from a given entity.
             *
             * @param entity The ID of the entity from which the component is to be removed.
             *
             * @return The type of the component that was removed, used to update the entity's signature.
             *
             * @throws assertion failure if the component type is not registered.
             */
            template<typename T>
            ComponentType RemoveComponent(Entity entity) {
                static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component!");

                T component;
                std::string component_name = component.GetName();
                assert(!component_name.empty() && "Component name not set!");
                assert(m_component_name_to_type.find(component_name) != m_component_name_to_type.end() && "Component not registered!");

                m_logging_manager->Log(LoggingType::DEBUG, "Removing Component \"" + component_name + "\" from"
                    " Entity \"" + std::to_string(entity) + "\"");
    
                std::shared_ptr<SparseSet<T, MAX_ENTITIES>> sparseSet = GetComponentSet<T>();
    
                // Removes entity from component sparse set
                sparseSet->Remove(entity);
    
                // If the last component is removed, the component array must be destroyed and unregistered
                if (sparseSet->Size() == 0) {
                    m_logging_manager->Log(LoggingType::DEBUG, "\tAll \"" + component_name + "\" Components removed... Destroying Component Array");
                    m_component_name_to_type.erase(component_name);
                    m_component_name_to_data.erase(component_name);
                    m_registered_components--;
                }
    
                // Return component type to update entity signature
                return m_component_name_to_type[component_name];
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
            T& GetComponentData(Entity entity) {
                return GetComponentSet<T>()->GetElement(entity);
            }
    
            template<typename T>
            ComponentType GetComponentType() {
                static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component!");

                T component;
                std::string component_name = component.GetName();
                assert(!component_name.empty() && "Component name not set!");
    
                if (m_component_name_to_type.find(component_name) == m_component_name_to_type.end()) {
                    return -1;
                }
                else {
                    return m_component_name_to_type[component_name];
                }
            }

            /**
             * @brief Get the registered Component Type using the Component Name
             * 
             * @param component_name Component Name to search
             * @return ComponentType
             * @return -1 if not found
             */
            ComponentType GetComponentType(std::string component_name);

            template<typename T>
            bool HasComponentType(Entity entity) const {
                return GetComponentSet<T>()->GetElement(entity) != nullptr;
            }

            /**
             * Retrieves the Component Name associated with the given component type.
             *
             * @param component_type The component type to retrieve the name for.
             *
             * @return The name associated with the given component type, or an empty string if the component is not registered.
             */
            std::string GetComponentName(ComponentType component_type);

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
            
        private:
            std::shared_ptr<LoggingManager> m_logging_manager;

            //Keeps track of the number of component types registered
            ComponentType m_registered_components;
    
            //Maps ComponentType id to Component Object Type name
            std::unordered_map<ComponentType, std::string> m_component_type_to_name;
    
            //Maps Component Object Type name to ComponentType id
            std::unordered_map<std::string, ComponentType> m_component_name_to_type;
    
            //Maps Component Object Type name to sparse set of component data
            //ComponentType names are the keys, sparse set of component data is the value
            std::unordered_map<std::string, std::shared_ptr<ISparseSet>> m_component_name_to_data;
    
            /**
             * Retrieves the sparse set of component data associated with the given component type.
             *
             * @tparam T The type of component data to be retrieved.
             *
             * @return A shared pointer to the sparse set of component data.
             *
             * @throws assertion failure if the component type is not registered.
             */
            template<typename T>
            std::shared_ptr<SparseSet<T, MAX_ENTITIES>> GetComponentSet() {
                static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component!");

                T component;
                std::string component_name = component.GetName();
                assert(!component_name.empty() && "Component name not set!");
                assert(m_component_name_to_data.find(component_name) != m_component_name_to_data.end() && "Component not registered!");
    
                return std::static_pointer_cast<SparseSet<T, MAX_ENTITIES>>(m_component_name_to_data[component_name]);
            }
    };
}