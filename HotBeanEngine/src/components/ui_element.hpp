/**
 * @file ui_element.hpp
 * @author Daniel Parker (DParker13)
 * @brief UI element component. Used for rendering UI elements.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "../core/core.hpp"

#include "enums/ui_type.hpp"

namespace Components {

    struct UIElement : public Component {
        Enums::UIType _type;
        bool _dirty = false;

        UIElement() {
            Component::_name = "UIElement";
        }

        std::string ToString() const override {
            return "UIElement";
        }
    };
}