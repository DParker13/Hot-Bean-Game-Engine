#include "text.hpp"

namespace GameObjects {
    Text::Text(Core::CoreManager* coreManager)
        : GameObject(coreManager) {
        _coreManager->AddComponent<Components::Transform>(_entity, Components::Transform());
        _coreManager->AddComponent<Components::Text>(_entity, Components::Text());
    }

    Components::Transform& Text::GetTransform() {
        return _coreManager->GetComponent<Components::Transform>(_entity);
    }

    Components::Text& Text::GetText() {
        return _coreManager->GetComponent<Components::Text>(_entity);
    }
    
    std::string Text::ToString() const {
        return _coreManager->ToString();
    };
}