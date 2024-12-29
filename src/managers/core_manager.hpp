#pragma once

#include <memory>
#include <unordered_map>

#include "ecs.hpp"
#include "entity_manager.hpp"
#include "component_manager.hpp"
#include "system_manager.hpp"

namespace Core {

    // CoreManager combines EntityManager and ComponentManager to manage entities and components together in one system
    class CoreManager {
    public:
        CoreManager();
        ~CoreManager();

        void Init();
        Entity CreateEntity();
        void DestroyEntity(Entity entity);
        void RemoveAllComponents(Entity entity);
        std::string ToString() const;

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
         * Registers a system of type T with the CoreManager.
         *
         * @tparam T The type of system to be registered.
         *
         * @return A shared pointer to the registered system.
         *
         * @throws assertion failure if the system type has already been registered.
         */
        template<typename T>
        T* RegisterSystem(T* system) {
            return _systemManager->RegisterSystem<T>(system);
        }

        /**
         * Sets the signature for a system that has already been registered with the CoreManager.
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

        template<typename System, typename Component>
        void SetSignature() {
            Signature& signature = _systemManager->GetSignature<System>();

            if (GetComponentType<Component>() == -1) {
                signature.set(RegisterComponentType<Component>());
            }
            else {
                signature.set(GetComponentType<Component>());
            }

            _systemManager->SetSignature<System>(signature);
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

    private:
        std::unique_ptr<EntityManager> _entityManager;
        std::unique_ptr<ComponentManager> _componentManager;
        std::unique_ptr<SystemManager> _systemManager;
    };
}