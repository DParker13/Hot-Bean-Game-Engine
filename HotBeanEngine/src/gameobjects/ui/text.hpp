#pragma once

#include "ui_element.hpp"
#include "../../components/text.hpp"

namespace GameObjects {
    namespace UI {
        struct Text : public UIElement<Components::Text> {
            Text()
                : UIElement<Components::Text>() {};
        };
    }
}