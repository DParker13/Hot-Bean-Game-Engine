#pragma once

#include "text.hpp"

namespace GameObjects {
    namespace UI {
        struct TextBox : public Text {
            TextBox(App& app)
                : Text(app) {};
        };
    }
}