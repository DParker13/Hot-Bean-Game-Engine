/**
 * @file component_manager.cpp
 * @author Daniel Parker (DParker13)
 * @brief Manages the entity-component relationship.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 */

#include <HotBeanEngine/application/managers/component_manager.hpp>

namespace HBE::Application::Managers {
    ComponentManager::ComponentManager(std::shared_ptr<LoggingManager> logging_manager)
        : m_logging_manager(logging_manager), m_registered_components(0) {}

    /**
     * @brief Retrieves the name of a component
     * 
     * @param component_id The type of the component
     * @return std::string The name of the component
     * @throw ComponentNotRegisteredException
     */
    std::string ComponentManager::GetComponentName(ComponentID component_id) {
        if (!IsComponentRegistered(component_id)) {
            auto ex = ComponentNotRegisteredException();
            LOG_CORE(LoggingType::ERROR, ex.what());
            throw ex;
        }

        return m_component_id_to_name[component_id];
    }

    /**
     * @brief Retrieves the Component Type associated with the given component name
     * 
     * @param component_name The name of the component
     * @return ComponentID The ComponentID associated with the given component name
     * @throw ComponentNotRegisteredException
     */
    ComponentID ComponentManager::GetComponentID(std::string component_name) {
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
     * @param entity EntityID to retrieve component from
     * @param component_id Type of component to retrieve
     * @return Component& Component data
     * @throws ComponentNotRegisteredException or std::bad_any_cast
     */
    IComponent* ComponentManager::GetComponent(EntityID entity, ComponentID component_id) {
        if (!IsComponentRegistered(component_id)) {
            auto ex = ComponentNotRegisteredException();
            LOG_CORE(LoggingType::ERROR, ex.what());
            throw ex;
        }
        
        try {
            std::string component_name = m_component_id_to_name[component_id];
            std::shared_ptr<ISparseSet> sparse_set = m_component_name_to_data[component_name];

            return std::any_cast<IComponent*>(sparse_set->GetElementPtrAsAny(entity));
        }
        catch (const std::bad_any_cast&) {
            LOG_CORE(LoggingType::ERROR, "Failed to cast component.");
            throw;
        }
    }

    /**
     * @brief Removes a component from an entity
     * 
     * @param entity EntityID to remove component from
     * @param component_id Type of component to remove
     * @throw ComponentNotRegisteredException
     */
    void ComponentManager::RemoveComponent(EntityID entity, ComponentID component_id) {
        if (!IsComponentRegistered(component_id)) {
            auto ex = ComponentNotRegisteredException();
            LOG_CORE(LoggingType::ERROR, ex.what());
            throw ex;
        }
        
        std::string component_name = m_component_id_to_name[component_id];
        auto sparse_set = m_component_name_to_data[component_name];

        if (!sparse_set->HasElement(entity)) {
            LOG_CORE(LoggingType::WARNING, "Component not associated with entity");
            return;
        }

        // Removes entity from component sparse set
        sparse_set->Remove(entity);

        // If the last component is removed, the component array must be destroyed and unregistered
        if (sparse_set->Size() == 0) {
            m_component_id_to_name.erase(component_id);
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
     * @param component_id The type of the component
     * @return true 
     * @return false 
     */
    bool ComponentManager::IsComponentRegistered(ComponentID component_id) const {
        return m_component_id_to_name.find(component_id) != m_component_id_to_name.end();
    }
}