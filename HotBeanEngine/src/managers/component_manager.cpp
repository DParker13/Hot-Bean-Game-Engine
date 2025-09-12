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

namespace HBE::Managers {
    ComponentManager::ComponentManager(std::shared_ptr<LoggingManager> logging_manager)
        : m_logging_manager(logging_manager), m_registered_components(0) {}

    /**
     * @brief Retrieves the name of a component
     * 
     * @param component_type The type of the component
     * @return std::string The name of the component
     * @throw ComponentNotRegisteredException
     */
    std::string ComponentManager::GetComponentName(ComponentType component_type) {
        if (!IsComponentRegistered(component_type)) {
            auto ex = ComponentNotRegisteredException();
            LOG_CORE(LoggingType::ERROR, ex.what());
            throw ex;
        }

        return m_component_type_to_name[component_type];
    }

    /**
     * @brief Retrieves the Component Type associated with the given component name
     * 
     * @param component_name The name of the component
     * @return ComponentType The ComponentType associated with the given component name
     * @throw ComponentNotRegisteredException
     */
    ComponentType ComponentManager::GetComponentType(std::string component_name) {
        if (!IsComponentRegistered(component_name)) {
            auto ex = ComponentNotRegisteredException(component_name);
            LOG_CORE(LoggingType::ERROR, ex.what());
            throw ex;
        }

        return m_component_name_to_type[component_name];
    }


    /**
     * @brief Retrieves a component from an entity
     * 
     * @param entity Entity to retrieve component from
     * @param component_type Type of component to retrieve
     * @return Component& Component data
     * @throws ComponentNotRegisteredException or std::bad_any_cast
     */
    Component& ComponentManager::GetComponent(Entity entity, ComponentType component_type) {
        if (!IsComponentRegistered(component_type)) {
            auto ex = ComponentNotRegisteredException();
            LOG_CORE(LoggingType::ERROR, ex.what());
            throw ex;
        }
        
        try {
            std::string component_name = m_component_type_to_name[component_type];
            auto component_sparse_set = m_component_name_to_data[component_name];

            Component* ptr = std::any_cast<Component*>(component_sparse_set->GetElementPtrAsAny(entity));
            return *ptr;
        }
        catch (const std::bad_any_cast& e) {
            LOG_CORE(LoggingType::ERROR, "Failed to cast component.");
            throw;
        }
    }

    /**
     * @brief Removes a component from an entity
     * 
     * @param entity Entity to remove component from
     * @param component_type Type of component to remove
     * @throw ComponentNotRegisteredException
     */
    void ComponentManager::RemoveComponent(Entity entity, ComponentType component_type) {
        if (!IsComponentRegistered(component_type)) {
            auto ex = ComponentNotRegisteredException();
            LOG_CORE(LoggingType::ERROR, ex.what());
            throw ex;
        }
        
        std::string component_name = m_component_type_to_name[component_type];
        auto sparse_set = m_component_name_to_data[component_name];

        if (!sparse_set->HasElement(entity)) {
            LOG_CORE(LoggingType::WARNING, "Component not associated with entity");
            return;
        }

        // Removes entity from component sparse set
        sparse_set->Remove(entity);

        // If the last component is removed, the component array must be destroyed and unregistered
        if (sparse_set->Size() == 0) {
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