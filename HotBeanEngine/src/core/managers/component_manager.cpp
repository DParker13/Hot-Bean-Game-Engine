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
        ComponentManager::ComponentManager() : _registeredComponents(0) {}
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
                return _componentTypeToName[component_type];
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
                return _componentNameToType[component_name];
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
            std::string component_name = _componentTypeToName[component_type];

            assert(_componentNameToType.find(component_name) != _componentNameToType.end() && "Component not registered!");
            auto componentSparseSet = _componentNameToData[component_name];

            return componentSparseSet->GetComponent(entity);
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
            void ComponentManager::RemoveComponent(Entity entity, ComponentType componentType) {
                std::string component_name = _componentTypeToName[componentType];
    
                assert(_componentNameToType.find(component_name) != _componentNameToType.end() && "Component not registered!");
                auto componentSparseSet = _componentNameToData[component_name];
    
                // Removes entity from component sparse set
                componentSparseSet->Remove(entity);
    
                // If the last component is removed, the component array must be destroyed and unregistered
                if (componentSparseSet->Size() == 0) {
                    _componentTypeToName.erase(componentType);
                    _componentNameToType.erase(component_name);
                    _componentNameToData.erase(component_name);
                    _registeredComponents--;
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
            return _componentNameToType.find(component_name) != _componentNameToType.end();
        }

        /**
         * @brief Checks if a component is registered
         * 
         * @param component_type The type of the component
         * @return true 
         * @return false 
         */
        bool ComponentManager::IsComponentRegistered(ComponentType component_type) const {
            return _componentTypeToName.find(component_type) != _componentTypeToName.end();
        }

        /**
         * Prints the contents of ComponentManager to the console. This is mostly for
         * debugging purposes and should be removed in a production build.
         */
        std::string ComponentManager::ToString() const {
            std::stringstream str;

            if(_componentNameToType.size() > 0) {
                str << "Component Manager: " << _registeredComponents << "\n";

                for (auto& [componentType, typeName] : _componentTypeToName) {
                    str << "  Component Type To Name: (" << componentType << "," << typeName << ")\n";
                }

                for (auto& [typeName, componentType] : _componentNameToType) {
                    str << "  Type Name To Component Type: (" << typeName << "," << componentType << ")\n";
                }

                for (auto& [name, sparseSet] : _componentNameToData) {

                    str << "  Component Name To Data: " << name << "\n";
                    str << sparseSet->ToString();
                }
                str << "\n";
            }

            return str.str();
        }
    }
}