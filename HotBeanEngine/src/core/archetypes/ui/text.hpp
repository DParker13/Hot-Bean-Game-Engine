#pragma once

#include "ui_element.hpp"

namespace GameObjects {
    namespace UI {
        struct Text : public UIElement<Core::Components::Text> {
            Text()
                : UIElement<Core::Components::Text>() {};
        };
    }
}