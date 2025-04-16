/**
 * @file ui_element.h
 * @author Daniel Parker (DParker13)
 * @brief UI element component. Used for rendering UI elements.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include <core.hpp>
#include "enums/ui_type.hpp"

namespace Components {

    struct UIElement : public Component {
        Enums::UIType _type;
        bool _dirty = false;

        UIElement() = default;

        std::string ToString() const override {
            return "UIElement";
        }
    };
}