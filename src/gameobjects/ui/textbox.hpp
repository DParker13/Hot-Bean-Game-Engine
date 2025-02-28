#pragma once

#include "text.hpp"

namespace GameObjects {
    namespace UI {
        class TextBox : public Text {
        public:
            TextBox(Core::CoreManager* coreManager);
        };
    }
}