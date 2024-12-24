#include "player.hpp"

namespace GameObjects {
    
    /**
     * Creates a new player object
     *
     * @param coreManager The CoreManager object managing the ECS
     */
    Player::Player(Core::CoreManager* coreManager)
        : GameObject(coreManager) {
        coreManager->AddComponent<Components::Transform>(entity, Components::Transform());
        coreManager->AddComponent<Components::Player>(entity, Components::Player());
    }

    Components::Transform& Player::GetTransform() {
        return coreManager->GetComponent<Components::Transform>(entity);
    }

    Components::Player& Player::GetPlayer() {
        return coreManager->GetComponent<Components::Player>(entity);
    }
    
    std::string Player::ToString() const {
        return coreManager->ToString();
    };
}