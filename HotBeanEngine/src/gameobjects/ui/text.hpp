#pragma once

#include "ui_element.hpp"

namespace GameObjects {
    namespace UI {
        struct Text : public UIElement<Components::Text> {
            Text()
                : UIElement<Components::Text>() {};
        };
    }
}