/**
 * @file component_manager.hpp
 * @author Daniel Parker (DParker13)
 * @brief Manages the entity-component relationship.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <memory>

#include <HotBeanEngine/application/managers/logging_manager.hpp>

namespace HBE::Application::Managers {
    using namespace HBE::Core;
    
    /**
     * @brief Manages component registration, addition, removal, and retrieval.
     * Uses sparse sets for efficient component storage and lookup.
     */
    class ComponentManager {
    private:
        std::shared_ptr<LoggingManager> m_logging_manager;

        //Keeps track of the number of component types registered
        ComponentID m_registered_components;

        //Maps ComponentID id to Component Object Type name
        std::unordered_map<ComponentID, std::string> m_component_id_to_name;

        //Maps Component Object Type name to ComponentID id
        std::unordered_map<std::string, ComponentID> m_component_name_to_type;

        //Maps Component Object Type name to sparse set of component data
        //ComponentID names are the keys, sparse set of component data is the value
        std::unordered_map<std::string, std::shared_ptr<ISparseSet>> m_component_name_to_data;
        
    public:
        ComponentManager(std::shared_ptr<LoggingManager> logging_manager);
        ~ComponentManager() = default;

        void RemoveComponent(EntityID entity, ComponentID component_id);
        IComponent* GetComponent(EntityID entity, ComponentID component_id);

        /**
         * @brief Registers a component type to the Component Manager
         * 
         * @tparam T Component type
         * @return ComponentID The ComponentID id
         * @throw MaxNumberOfComponentsRegisteredException
         */
        template<typename T>
        ComponentID RegisterComponentID() {
            try {
                static_assert(std::is_base_of_v<IComponent, T>, "T must inherit from Component");

                if (m_registered_components >= MAX_COMPONENTS) {
                    auto ex = MaxNumberOfComponentsRegisteredException();
                    LOG_CORE(LoggingType::ERROR, ex.what());
                    throw ex;
                }

                std::string component_name = std::string(GetComponentName<T>());

                LOG_CORE(LoggingType::DEBUG, "Registering Component \"" + component_name + "\"");
    
                ComponentID component_id = m_registered_components;

                LOG_CORE(LoggingType::DEBUG, "\tComponentID \"" + std::to_string(component_id) + "\"");
    
                // Maps ComponentID id to Component Object Type name
                m_component_id_to_name[component_id] = component_name;
    
                // Maps ComponentID to an id
                m_component_name_to_type[component_name] = component_id;
    
                // Create new sparse set for component data
                m_component_name_to_data[component_name] = std::make_shared<SparseSet<T, MAX_ENTITIES>>();
    
                m_registered_components++;

                LOG_CORE(LoggingType::DEBUG, "\t" + std::to_string(m_registered_components) + " Registered Components");
    
                return component_id;
            }
            catch (const std::exception&) {
                throw;
            }
        }

        template<typename T>
        ComponentID AddComponent(EntityID entity) {
            try {
                static_assert(std::is_base_of_v<IComponent, T>, "T must inherit from Component");

                std::string component_name = std::string(GetComponentName<T>());

                LOG_CORE(LoggingType::DEBUG, "Adding Empty Component \"" + component_name + "\" to"
                        " EntityID \"" + std::to_string(entity) + "\"");
    
                // Register component type if it's not already registered
                if (!IsComponentRegistered(component_name)) {
                    LOG_CORE(LoggingType::DEBUG, "\tEmpty Component \"" + component_name + "\" not registered... Attempting to Register");

                    RegisterComponentID<T>();
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
         * @param entity EntityID to add component to
         * @param component_data Component data
         * @return ComponentID 
         */
        template<typename T>
        ComponentID AddComponent(EntityID entity, T& component_data) {
            try {
                static_assert(std::is_base_of_v<IComponent, T>, "T must inherit from Component");

                std::string component_name = std::string(GetComponentName<T>());

                LOG_CORE(LoggingType::DEBUG, "Adding Component \"" + component_name + "\" to"
                        " EntityID \"" + std::to_string(entity) + "\"");
    
                // Register the component type if it's not already registered
                if (!IsComponentRegistered(component_name)) {
                    LOG_CORE(LoggingType::DEBUG, "\tComponent \"" + component_name + "\" not registered... Attempting to Register");

                    RegisterComponentID<T>();
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
        void RemoveComponent(EntityID entity) {
            try{
                static_assert(std::is_base_of_v<IComponent, T>, "T must inherit from Component");

                std::string component_name = std::string(GetComponentName<T>());

                LOG_CORE(LoggingType::DEBUG, "Removing Component \"" + component_name + "\" from"
                        " EntityID \"" + std::to_string(entity) + "\"");

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
         * @param entity EntityID to get component data from
         * @return T& The component data
         */
        template<typename T>
        T& GetComponentData(EntityID entity) {
            try {
                return GetComponentSet<T>()->GetElementAsRef(entity);
            }
            catch (const std::exception&) {
                throw;
            }
        }

        /**
         * @brief Get the Component Type object
         * 
         * @tparam T The type of component
         * @return ComponentID 
         */
        template<typename T>
        ComponentID GetComponentID() {
            try {
                static_assert(std::is_base_of_v<IComponent, T>, "T must inherit from Component");

                if (!IsComponentRegistered<T>()) {
                    auto ex = ComponentNotRegisteredException(std::string(GetComponentName<T>()));
                    LOG_CORE(LoggingType::ERROR, ex.what());
                    throw ex;
                }
                else {
                    return m_component_name_to_type[std::string(GetComponentName<T>())];
                }
            }
            catch (const std::exception&) {
                throw;
            }
        }

        /**
         * @brief Retrieves the Component Type associated with the given component name
         * 
         * @param component_name The name of the component
         * @return ComponentID The ComponentID associated with the given component name
         */
        ComponentID GetComponentID(std::string component_name);

        /**
         * @brief Checks if an entity has a component of type T
         * 
         * @tparam T The type of component
         * @param entity The entity to check
         * @return true if the entity is mapped to a component of type T, false otherwise
         */
        template<typename T>
        bool HasComponent(EntityID entity) const {
            try {
                return GetComponentSet<T>()->HasElement(entity);
            }
            catch(const std::exception&) {
                return false;
            }
        }

        /**
         * @brief Retrieves the Component Name associated with the given component type.
         *
         * @param component_id The component type to retrieve the name for.
         * @return The name associated with the given component type, or an empty string if the component is not registered.
         */
        std::string GetComponentName(ComponentID component_id);

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
         * @param component_id The type of the component
         * @return true 
         * @return false 
         */
        bool IsComponentRegistered(ComponentID component_id) const;

        template<typename T>
        bool IsComponentRegistered() const {
            return m_component_name_to_type.find(std::string(GetComponentName<T>())) != m_component_name_to_type.end();
        }

    private:
        /**
         * @brief Retrieves the sparse set of component data associated with the given component type.
         *
         * @tparam T The type of component data to be retrieved.
         * @return A shared pointer to the sparse set of component data.
         * @throw ComponentNotRegisteredException
         */
        template<typename T>
        std::shared_ptr<SparseSet<T, MAX_ENTITIES>> GetComponentSet() const {
            try {
                if (!IsComponentRegistered<T>()) {
                    auto ex = ComponentNotRegisteredException(std::string(GetComponentName<T>()));
                    LOG_CORE(LoggingType::ERROR, ex.what());
                    throw ex;
                }

                return std::static_pointer_cast<SparseSet<T, MAX_ENTITIES>>(m_component_name_to_data.at(std::string(GetComponentName<T>())));
            }
            catch (const std::exception&) {
                throw;
            }
        }

        /**
         * @brief Retrieves the name of the component
         * 
         * @tparam T The type of component
         * @return std::string The name of the component
         */
        template<typename T>
        std::string_view GetComponentName() const {
            static_assert(std::is_base_of_v<IComponent, T>, "T must inherit from Component");
            static_assert(has_static_get_name<T>::value, "T must have a StaticGetName() function");

            if (T::StaticGetName().empty()) {
                LOG_CORE(LoggingType::WARNING, "Component name is empty");
            }

            return T::StaticGetName();
        }
    };
}