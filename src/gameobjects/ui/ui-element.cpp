#include "ui-element.hpp"

namespace GameObjects {
    namespace UI {
        UIElement::UIElement(Core::CoreManager* coreManager)
            : GameObject(coreManager) {
            _coreManager->AddComponent<Components::Transform2D>(_entity, Components::Transform2D());
            _coreManager->AddComponent<Components::Texture>(_entity, Components::Texture());
        }

        Components::Transform2D& UIElement::GetTransform2D() {
            return _coreManager->GetComponent<Components::Transform2D>(_entity);
        }

        Components::Texture& UIElement::GetTexture() {
            return _coreManager->GetComponent<Components::Texture>(_entity);
        }
        
        std::string UIElement::ToString() const {
            return _coreManager->ToString();
        };
    }
}