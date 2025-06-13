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

#include "../../ecs/all_ecs.hpp"

namespace Core::Components {

    struct UIElement : public Component {
        enum class UIType {
            Empty, // Placeholder if UI element is not setup correctly
            Text,
            TextBox,
            Image,
            Button,
            Slider,
            Dropdown,
            Checkbox,
            Radio,
        };

        UIType m_type = UIType::Empty;
        bool m_dirty = true;

        UIElement() = default;

        virtual std::string GetName() const override {
            return "UIElement";
        }

        virtual void Serialize(YAML::Emitter& out) const override {
            out << YAML::Key << "type" << YAML::Value << (int)m_type;
        }

        virtual void Deserialize(YAML::Node& node) override {
            if (node["type"]) {
                m_type = (UIType)node["type"].as<int>();
            }

            if (node["dirty"]) {
                m_dirty = node["dirty"].as<bool>();
            }
        }
    };
}