#include "core_manager.hpp"

namespace Core {
    CoreManager::CoreManager() {}
    CoreManager::~CoreManager() = default;

    /**
     * Initializes the CoreManager by creating instances of the EntityManager and ComponentManager.
     */
    void CoreManager::Init() {
        _entityManager = std::make_unique<EntityManager>();
        _componentManager = std::make_unique<ComponentManager>();
        _systemManager = std::make_unique<SystemManager>();
    }

    /**
     * Creates a new entity and returns its unique identifier.
     *
     * @return The unique identifier of the newly created entity.
     *
     * @throws assertion failure if the maximum number of entities has been reached.
     */
    Entity CoreManager::CreateEntity() {
        return _entityManager->CreateEntity();
    }

    /**
     * Destroys an entity and releases its resources.
     *
     * @param entity The ID of the entity to destroy.
     *
     * @throws assertion failure if the entity ID is out of range or invalid.
     */
    void CoreManager::DestroyEntity(Entity entity) {
        _entityManager->DestroyEntity(entity);
        RemoveAllComponents(entity);
    }

    /**
     * Removes all components associated with a given entity.
     *
     * @param entity The ID of the entity from which all components are to be removed.
     *
     * This function retrieves the signature of the entity, which represents the
     * components attached to the entity. It iterates over each component type
     * indicated by the signature and removes the corresponding components from
     * the component manager.
     */
    void CoreManager::RemoveAllComponents(Entity entity) {
        Signature signature = _entityManager->GetSignature(entity);

        for (int i = 0; i < signature.count(); i++) {
            if(signature[i]) {
                _componentManager->RemoveComponent(entity, i);
            }
        }
    }

    /**
     * Prints out the state of the ComponentManager for debugging purposes.
     */
    void CoreManager::Print() const {
        _entityManager->Print();
        _componentManager->Print();
        _systemManager->Print();
    }
}