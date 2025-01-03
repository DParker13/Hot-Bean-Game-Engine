#include "player.hpp"

namespace GameObjects {
    
    /**
     * Creates a new player object
     *
     * @param coreManager The CoreManager object managing the ECS
     */
    Player::Player(Core::CoreManager* coreManager)
        : GameObject(coreManager) {
        _coreManager->AddComponent<Components::Transform>(_entity, Components::Transform());
        _coreManager->AddComponent<Components::Player>(_entity, Components::Player());
    }

    Components::Transform& Player::GetTransform() {
        return _coreManager->GetComponent<Components::Transform>(_entity);
    }

    Components::Player& Player::GetPlayer() {
        return _coreManager->GetComponent<Components::Player>(_entity);
    }
    
    std::string Player::ToString() const {
        return _coreManager->ToString();
    };
}