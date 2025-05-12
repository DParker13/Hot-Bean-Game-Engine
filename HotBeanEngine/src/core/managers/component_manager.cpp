/**
 * @file component_manager.cpp
 * @author Daniel Parker (DParker13)
 * @brief Manages the entity-component relationship.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "component_manager.hpp"

namespace Core {
    namespace Managers {
        ComponentManager::ComponentManager(std::shared_ptr<LoggingManager> logging_manager)
            : m_logging_manager(logging_manager), m_registered_components(0) {}
        ComponentManager::~ComponentManager() = default;

        /**
         * Retrieves the Component Name associated with the given component type.
         *
         * @param component_type The component type to retrieve the name for.
         *
         * @return The name associated with the given component type, or an empty string if the component is not registered.
         */
        std::string ComponentManager::GetComponentName(ComponentType component_type) {
            if(IsComponentRegistered(component_type)) {
                return m_component_type_to_name[component_type];
            }
            else {
                return "";
            }
        }

        /**
         * @brief Get the registered Component Type using the Component Name
         * 
         * @param component_name Component Name to search
         * @return ComponentType
         * @return -1 if not found
         */
        ComponentType ComponentManager::GetComponentType(std::string component_name) {
            if(IsComponentRegistered(component_name)) {
                return m_component_name_to_type[component_name];
            }
            else {
                return -1;
            }
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
        Component& ComponentManager::GetComponent(Entity entity, ComponentType component_type) {
            std::string component_name = m_component_type_to_name[component_type];

            assert(m_component_name_to_type.find(component_name) != m_component_name_to_type.end() && "Component not registered!");
            auto component_sparse_set = m_component_name_to_data[component_name];

            return component_sparse_set->GetComponent(entity);
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
            void ComponentManager::RemoveComponent(Entity entity, ComponentType component_type) {
                std::string component_name = m_component_type_to_name[component_type];
    
                assert(m_component_name_to_type.find(component_name) != m_component_name_to_type.end() && "Component not registered!");
                auto component_sparse_set = m_component_name_to_data[component_name];
    
                // Removes entity from component sparse set
                component_sparse_set->Remove(entity);
    
                // If the last component is removed, the component array must be destroyed and unregistered
                if (component_sparse_set->Size() == 0) {
                    m_component_type_to_name.erase(component_type);
                    m_component_name_to_type.erase(component_name);
                    m_component_name_to_data.erase(component_name);
                    m_registered_components--;
                }
            }

        /**
         * @brief Checks if a component is registered
         * 
         * @param component_name The name of the component
         * @return true 
         * @return false 
         */
        bool ComponentManager::IsComponentRegistered(std::string component_name) const {
            return m_component_name_to_type.find(component_name) != m_component_name_to_type.end();
        }

        /**
         * @brief Checks if a component is registered
         * 
         * @param component_type The type of the component
         * @return true 
         * @return false 
         */
        bool ComponentManager::IsComponentRegistered(ComponentType component_type) const {
            return m_component_type_to_name.find(component_type) != m_component_type_to_name.end();
        }
    }
}