#include "gameobject.hpp"

namespace GameObjects {

    GameObject::GameObject(Core::CoreManager* coreManager)
        : _coreManager(coreManager) {
        _entity = coreManager->CreateEntity();
    }

    Entity GameObject::GetEntity() {
        return _entity;
    }
}