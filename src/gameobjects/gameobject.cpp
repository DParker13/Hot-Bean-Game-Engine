#include "gameobject.hpp"

namespace GameObjects {

    GameObject::GameObject(Core::CoreManager* coreManager)
        : coreManager(coreManager) {
        entity = coreManager->CreateEntity();
    }
}