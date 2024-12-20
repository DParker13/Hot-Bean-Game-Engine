#include "player.hpp"

namespace GameObjects {
    Player::Player(Core::CoreManager* coreManager)
        : coreManager(coreManager) {
        entity = coreManager->CreateEntity();
        
        coreManager->AddComponent<Components::Transform>(entity, Components::Transform());
        coreManager->AddComponent<Components::Player>(entity, Components::Player());
    }

    Components::Transform& Player::GetTransform() {
        return coreManager->GetComponent<Components::Transform>(entity);
    }

    Components::Player& Player::GetPlayer() {
        return coreManager->GetComponent<Components::Player>(entity);
    }
    
    std::string Player::ToString(Core::CoreManager& coreManager) const {
        return coreManager.ToString();
    };
}