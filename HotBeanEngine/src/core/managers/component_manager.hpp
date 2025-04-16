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
#include <cassert>
#include <sstream>

#include "../ecs/all_ecs.hpp"

using namespace Core::ECS;

namespace Core {
    namespace Managers {
        // ComponentManager manages the creation and destruction of components for entities
        class ComponentManager {
            public:
                ComponentManager();
                ~ComponentManager();
        
                std::string ToString() const;
        
                /**
                 * Registers a component type with the ComponentManager and assigns it a ComponentType id.
                 *
                 * @param typeName The name of the component type to be registered as a string.
                 *
                 * @throws assertion failure if the maximum number of component types has been reached.
                 */
                template<typename T>
                ComponentType RegisterComponentType() {
                    std::string typeName = typeid(T).name();
        
                    static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component!");
                    assert(_registeredComponents < MAX_COMPONENTS && "Reached maximum number of component!");
        
                    ComponentType componentType = _registeredComponents;
        
                    // Maps ComponentType id to Component Object Type name
                    _componentTypeToName[componentType] = typeName;
        
                    // Maps ComponentType to an id
                    _componentNameToType[typeName] = componentType;
        
                    // Create new sparse set for component data
                    _componentNameToData[typeName] = std::make_shared<SparseSet<T, MAX_ENTITIES>>();
        
                    _registeredComponents++;
        
                    return componentType;
                }

                /**
                 * Registers a component type with the ComponentManager and assigns it a ComponentType id.
                 *
                 * @param typeName The name of the component type to be registered as a string.
                 *
                 * @throws assertion failure if the maximum number of component types has been reached.
                 */
                template<typename T>
                ComponentType RegisterComponentType(std::string typeName) {
                    static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component!");
                    assert(_registeredComponents < MAX_COMPONENTS && "Reached maximum number of component!");
        
                    ComponentType componentType = _registeredComponents;
        
                    // Maps ComponentType id to Component Object Type name
                    _componentTypeToName[componentType] = typeName;
        
                    // Maps ComponentType to an id
                    _componentNameToType[typeName] = componentType;
        
                    // Create new sparse set for component data
                    _componentNameToData[typeName] = std::make_shared<SparseSet<T, MAX_ENTITIES>>();
        
                    _registeredComponents++;
        
                    return componentType;
                }
        
                /*
                When you add a component to an entity, check if the component is registered.
                If a component is not registered, a component array must be created.
                This array keeps track of the entities that have that component.
                This function creates a unique signature for all the components.
                */
                template<typename T>
                ComponentType AddComponent(Entity entity, T& componentData) {
                    static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component!");
                    
                    // Component Type Name
                    std::string typeName = typeid(T).name();
        
                    // Register component type if it's not already registered
                    if (_componentNameToType.find(typeName) == _componentNameToType.end()) {
                        RegisterComponentType<T>();
                    }
        
                    GetComponentSet<T>()->Insert(entity, componentData);
                    return _componentNameToType[typeName];
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
                    // Component Type Name
                    std::string typeName = typeid(T).name();
        
                    assert(_componentNameToType.find(typeName) != _componentNameToType.end() && "Component not registered!");
        
                    std::shared_ptr<SparseSet<T, MAX_ENTITIES>> sparseSet = GetComponentSet<T>();
        
                    // Removes entity from component sparse set
                    sparseSet->Remove(entity);
        
                    // If the last component is removed, the component array must be destroyed and unregistered
                    if (sparseSet->Size() == 0) {
                        _componentNameToType.erase(typeName);
                        _componentNameToData.erase(typeName);
                        _registeredComponents--;
                    }
        
                    // Return component type to update entity signature
                    return _componentNameToType[typeName];
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
                void RemoveComponent(Entity entity, ComponentType componentType) {
                    // Component Type Name
                    std::string typeName = _componentTypeToName[componentType];
        
                    assert(_componentNameToType.find(typeName) != _componentNameToType.end() && "Component not registered!");
                    auto componentSparseSet = _componentNameToData[typeName];
        
                    // Removes entity from component sparse set
                    componentSparseSet->Remove(entity);
        
                    // If the last component is removed, the component array must be destroyed and unregistered
                    if (componentSparseSet->Size() == 0) {
                        _componentTypeToName.erase(componentType);
                        _componentNameToType.erase(typeName);
                        _componentNameToData.erase(typeName);
                        _registeredComponents--;
                    }
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
                    std::string typeName = typeid(T).name();
        
                    if (_componentNameToType.find(typeName) == _componentNameToType.end()) {
                        return -1;
                    }
                    else {
                        return _componentNameToType[typeName];
                    }
                }
                
            private:
                //Keeps track of the number of component types registered
                ComponentType _registeredComponents;
        
                //Maps ComponentType id to Component Object Type name
                std::unordered_map<ComponentType, std::string> _componentTypeToName;
        
                //Maps Component Object Type name to ComponentType id
                std::unordered_map<std::string, ComponentType> _componentNameToType;
        
                //Maps Component Object Type name to sparse set of component data
                //ComponentType names are the keys, sparse set of component data is the value
                std::unordered_map<std::string, std::shared_ptr<ISparseSet>> _componentNameToData;
        
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
                    std::string typeName = typeid(T).name();
        
                    assert(_componentNameToData.find(typeName) != _componentNameToData.end() && "Component not registered!");
        
                    return std::static_pointer_cast<SparseSet<T, MAX_ENTITIES>>(_componentNameToData[typeName]);
                }
        
                /**
                 * Retrieves the name of the component type associated with a given component type.
                 *
                 * @param componentType The component type to retrieve the name for.
                 *
                 * @return The name associated with the given component type, or an empty string if the component is not registered.
                 */
                std::string GetComponentTypeName(ComponentType componentType) {
                    if(_componentTypeToName.find(componentType) != _componentTypeToName.end()) {
                        return _componentTypeToName[componentType];
                    }
                    else {
                        return "";
                    }
                }
        };
    }
}