#include "text.hpp"

namespace GameObjects {
    Text::Text(Core::CoreManager* coreManager)
        : GameObject(coreManager) {
        coreManager->AddComponent<Components::Transform>(entity, Components::Transform());
        coreManager->AddComponent<Components::Text>(entity, Components::Text());
    }

    Components::Transform& Text::GetTransform() {
        return coreManager->GetComponent<Components::Transform>(entity);
    }

    Components::Text& Text::GetText() {
        return coreManager->GetComponent<Components::Text>(entity);
    }
    
    std::string Text::ToString() const {
        return coreManager->ToString();
    };
}