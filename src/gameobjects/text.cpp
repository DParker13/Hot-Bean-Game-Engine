#include "text.hpp"

namespace GameObjects {
    Text::Text(Core::CoreManager* coreManager)
        : GameObject(coreManager) {
        _coreManager->AddComponent<Components::Transform>(_entity, Components::Transform());
        _coreManager->AddComponent<Components::Text>(_entity, Components::Text());
        _coreManager->AddComponent<Components::Texture>(_entity, Components::Texture());
    }

    Components::Transform& Text::GetTransform() {
        return _coreManager->GetComponent<Components::Transform>(_entity);
    }

    Components::Text& Text::GetText() {
        return _coreManager->GetComponent<Components::Text>(_entity);
    }

    Components::Texture& Text::GetTexture() {
        return _coreManager->GetComponent<Components::Texture>(_entity);
    }
    
    std::string Text::ToString() const {
        return _coreManager->ToString();
    };
}