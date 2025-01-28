#include "gameobject.hpp"

namespace GameObjects {

    GameObject::GameObject(Core::CoreManager* coreManager)
        : _coreManager(coreManager) {
        _entity = coreManager->CreateEntity();
    }

    GameObject::~GameObject() {
        _coreManager->DestroyEntity(_entity);
    }

    Entity GameObject::GetEntity() {
        return _entity;
    }
}