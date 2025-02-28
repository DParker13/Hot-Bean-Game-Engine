#include "player.hpp"

namespace GameObjects {
    
    /**
     * Creates a new player object
     *
     * @param coreManager The CoreManager object managing the ECS
     */
    Player::Player(Core::CoreManager* coreManager)
        : GameObject(coreManager) {
        _coreManager->AddComponent<Components::Transform2D>(_entity, Components::Transform2D());
        _coreManager->AddComponent<Components::Controller>(_entity, Components::Controller());
    }

    Components::Transform2D& Player::GetTransform2D() {
        return _coreManager->GetComponent<Components::Transform2D>(_entity);
    }

    Components::Controller& Player::GetController() {
        return _coreManager->GetComponent<Components::Controller>(_entity);
    }
    
    std::string Player::ToString() const {
        return _coreManager->ToString();
    };
}