#include "text.hpp"

namespace GameObjects {
    namespace UI {
        Text::Text(Core::CoreManager* coreManager)
            : UIElement(coreManager) {
            _coreManager->AddComponent<Components::Text>(_entity, Components::Text());
        }

        Components::Text& Text::GetText() {
            return _coreManager->GetComponent<Components::Text>(_entity);
        }
        
        std::string Text::ToString() const {
            return _coreManager->ToString();
        };
    }
}