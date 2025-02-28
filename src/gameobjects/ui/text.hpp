#pragma once

#include "ui-element.hpp"
#include "../../components/text.hpp"

namespace GameObjects {
    namespace UI {
        class Text : public UIElement {
        public:
            Text(Core::CoreManager* coreManager);
            
            Components::Text& GetText();
            std::string ToString() const override;
        };
    }
}