/**
 * @file component_manager.hpp
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
using namespace Config;

namespace Core::Managers {
    // ComponentManager manages the creation and destruction of components for entities
    class ComponentManager {
        public:
            ComponentManager(std::shared_ptr<LoggingManager> logging_manager);
            ~ComponentManager() = default;
    
            void RemoveComponent(Entity entity, ComponentType component_type);
            Component& GetComponent(Entity entity, ComponentType component_type);

            /**
             * @brief Registers a component type to the Component Manager
             * 
             * @tparam T Component type
             * @return ComponentType The ComponentType id
             * @throw MaxNumberOfComponentsRegisteredException
             */
            template<typename T>
            ComponentType RegisterComponentType() {
                try {
                    static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component");

                    if (m_registered_components >= MAX_COMPONENTS) {
                        auto ex = MaxNumberOfComponentsRegisteredException();
                        LOG_CORE(LoggingType::ERROR, ex.what());
                        throw ex;
                    }

                    std::string component_name = GetComponentName<T>();

                    LOG_CORE(LoggingType::DEBUG, "Registering Component \"" + component_name + "\"");
        
                    ComponentType component_type = m_registered_components;

                    LOG_CORE(LoggingType::DEBUG, "\tComponentType \"" + std::to_string(component_type) + "\"");
        
                    // Maps ComponentType id to Component Object Type name
                    m_component_type_to_name[component_type] = component_name;
        
                    // Maps ComponentType to an id
                    m_component_name_to_type[component_name] = component_type;
        
                    // Create new sparse set for component data
                    m_component_name_to_data[component_name] = std::make_shared<SparseSet<T, MAX_ENTITIES>>();
        
                    m_registered_components++;

                    LOG_CORE(LoggingType::DEBUG, "\t" + std::to_string(m_registered_components) + " Registered Components");
        
                    return component_type;
                }
                catch (const std::exception& e) {
                    throw;
                }
            }

            template<typename T>
            ComponentType AddComponent(Entity entity) {
                try {
                    static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component");

                    std::string component_name = GetComponentName<T>();

                    LOG_CORE(LoggingType::DEBUG, "Adding Empty Component \"" + component_name + "\" to"
                            " Entity \"" + std::to_string(entity) + "\"");
        
                    // Register component type if it's not already registered
                    if (!IsComponentRegistered(component_name)) {
                        LOG_CORE(LoggingType::DEBUG, "\tEmpty Component \"" + component_name + "\" not registered... Attempting to Register");

                        RegisterComponentType<T>();
                    }

                    std::shared_ptr<SparseSet<T, MAX_ENTITIES>> sparse_set = GetComponentSet<T>();

                    if (sparse_set->HasElement(entity)) {
                        LOG_CORE(LoggingType::WARNING, "Component already added to entity!");
                        return m_component_name_to_type[component_name];
                    }
        
                    sparse_set->InsertEmpty(entity);
                    return m_component_name_to_type[component_name];
                }
                catch (const std::exception& e) {
                    throw;
                }
            }
    
            /**
             * @brief Adds a component of type T to a given entity.
             * 
             * @tparam T Component type
             * @param entity Entity to add component to
             * @param component_data Component data
             * @return ComponentType 
             */
            template<typename T>
            ComponentType AddComponent(Entity entity, T& component_data) {
                try {
                    static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component");

                    std::string component_name = GetComponentName<T>();

                    LOG_CORE(LoggingType::DEBUG, "Adding Component \"" + component_name + "\" to"
                            " Entity \"" + std::to_string(entity) + "\"");
        
                    // Register the component type if it's not already registered
                    if (!IsComponentRegistered(component_name)) {
                        LOG_CORE(LoggingType::DEBUG, "\tComponent \"" + component_name + "\" not registered... Attempting to Register");

                        RegisterComponentType<T>();
                    }

                    std::shared_ptr<SparseSet<T, MAX_ENTITIES>> sparse_set = GetComponentSet<T>();

                    if (sparse_set->HasElement(entity)) {
                        LOG_CORE(LoggingType::WARNING, "Component already added to entity!");
                        return m_component_name_to_type[component_name];
                    }
        
                    sparse_set->Insert(entity, component_data);
                    return m_component_name_to_type[component_name];
                }
                catch (std::runtime_error& e) {
                    LOG_CORE(LoggingType::ERROR, "Exception type: " + std::string(typeid(e).name()) + ", Message: " + e.what());
                    throw;
                }
            }
            
            /**
             * @brief Removes a component of type T from a given entity.
             *
             * @param entity The ID of the entity from which the component is to be removed.
             * @return The type of the component that was removed, used to update the entity's signature.
             */
            template<typename T>
            void RemoveComponent(Entity entity) {
                try{
                    static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component");

                    std::string component_name = GetComponentName<T>();

                    LOG_CORE(LoggingType::DEBUG, "Removing Component \"" + component_name + "\" from"
                            " Entity \"" + std::to_string(entity) + "\"");

                    std::shared_ptr<SparseSet<T, MAX_ENTITIES>> sparse_set = GetComponentSet<T>();

                    // Check if entity has component
                    if (!sparse_set->HasElement(entity)) {
                        LOG_CORE(LoggingType::WARNING, "Component not associated with entity");
                        return;
                    }

                    // Removes entity from component sparse set
                    sparse_set->Remove(entity);

                    // If the last component is removed, the component array must be destroyed and unregistered
                    if (sparse_set->Size() == 0) {
                        LOG_CORE(LoggingType::DEBUG, "\tAll \"" + component_name + "\" Components removed... Destroying Component Array");

                        m_component_name_to_type.erase(component_name);
                        m_component_name_to_data.erase(component_name);
                        m_registered_components--;
                    }
                }
                catch (const std::exception& e) {
                    throw;
                }
            }
    
            /**
             * @brief Get the Component object data
             * 
             * @tparam T The type of component
             * @param entity Entity to get component data from
             * @return T& The component data
             */
            template<typename T>
            T& GetComponentData(Entity entity) {
                try {
                    return GetComponentSet<T>()->GetElementAsRef(entity);
                }
                catch (const std::exception& e) {
                    throw;
                }
            }
    
            /**
             * @brief Get the Component Type object
             * 
             * @tparam T The type of component
             * @return ComponentType 
             */
            template<typename T>
            ComponentType GetComponentType() {
                try {
                    static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component");

                    std::string component_name = GetComponentName<T>();
        
                    if (!IsComponentRegistered(component_name)) {
                        auto ex = ComponentNotRegisteredException(component_name);
                        LOG_CORE(LoggingType::ERROR, ex.what());
                        throw ex;
                    }
                    else {
                        return m_component_name_to_type[component_name];
                    }
                }
                catch (const std::exception& e) {
                    throw;
                }
            }

            /**
             * @brief Retrieves the Component Type associated with the given component name
             * 
             * @param component_name The name of the component
             * @return ComponentType The ComponentType associated with the given component name
             */
            ComponentType GetComponentType(std::string component_name);

            /**
             * @brief Checks if an entity has a component of type T
             * 
             * @tparam T The type of component
             * @param entity The entity to check
             * @return true if the entity is mapped to a component of type T, false otherwise
             */
            template<typename T>
            bool HasComponent(Entity entity) const {
                try {
                    return GetComponentSet<T>()->HasElement(entity);
                }
                catch(const std::exception& e) {
                    return false;
                }
            }

            /**
             * @brief Retrieves the Component Name associated with the given component type.
             *
             * @param component_type The component type to retrieve the name for.
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

            template<typename T>
            bool IsComponentRegistered() const {
                try {
                    return m_component_name_to_type.find(GetComponentName<T>()) != m_component_name_to_type.end();
                }
                catch (const ComponentNameNotDefinedException& e) {
                    throw;
                }
            }

        private:
            /**
             * @brief Retrieves the sparse set of component data associated with the given component type.
             *
             * @tparam T The type of component data to be retrieved.
             * @return A shared pointer to the sparse set of component data.
             */
            template<typename T>
            std::shared_ptr<SparseSet<T, MAX_ENTITIES>> GetComponentSet() const {
                try {
                    static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component");

                    return GetComponentSet<T>(GetComponentName<T>());
                }
                catch (const std::exception& e) {
                    throw;
                }
            }

            /**
             * @brief Retrieves the sparse set of component data associated with the given component type.
             *
             * @tparam T The type of component data to be retrieved.
             * @return A shared pointer to the sparse set of component data.
             * @throw ComponentNotRegisteredException
             */
            template<typename T>
            std::shared_ptr<SparseSet<T, MAX_ENTITIES>> GetComponentSet(const std::string& component_name) const {
                try {
                    static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component");

                    if (!IsComponentRegistered(component_name)) {
                        auto ex = ComponentNotRegisteredException(component_name);
                        LOG_CORE(LoggingType::ERROR, ex.what());
                        throw ex;
                    }
        
                    return std::static_pointer_cast<SparseSet<T, MAX_ENTITIES>>(m_component_name_to_data.at(component_name));
                }
                catch (const std::exception& e) {
                    throw;
                }
            }

            /**
             * @brief Retrieves the name of the component
             * 
             * @tparam T The type of component
             * @return std::string The name of the component
             * @throw ComponentNameNotDefinedException
             */
            template<typename T>
            std::string GetComponentName() const {
                static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component");

                T component;
                std::string component_name = component.GetName();

                if (component_name.empty()) {
                    auto ex = ComponentNameNotDefinedException();
                    LOG_CORE(LoggingType::ERROR, ex.what());
                    throw ex;
                }

                return component_name;
            }
            
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
    };
}