#include "text.hpp"

namespace GameObjects {
    Text::Text(Core::CoreManager* coreManager)
        : coreManager(coreManager) {
        entity = coreManager->CreateEntity();
        
        coreManager->AddComponent<Components::Transform>(entity, Components::Transform());
        coreManager->AddComponent<Components::Text>(entity, Components::Text());
    }

    Components::Transform& Text::GetTransform() {
        return coreManager->GetComponent<Components::Transform>(entity);
    }

    Components::Text& Text::GetText() {
        return coreManager->GetComponent<Components::Text>(entity);
    }
    
    std::string Text::ToString(Core::CoreManager& coreManager) const {
        return coreManager.ToString();
    };
}