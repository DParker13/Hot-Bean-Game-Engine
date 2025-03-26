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

namespace Components {

    struct UIElement : public Component {
        UIType _type;
    };

    enum UIType {
        Text,
        Image,
        Button,
        Slider,
        Dropdown,
        Checkbox,
        Radio,
    };
}