/**
 * @file ui_element.hpp
 * @author Daniel Parker (DParker13)
 * @brief UI element component. Used for rendering UI elements.
 * @version 0.1
 * @date 2025-02-23
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <HotBeanEngine/core/all_core.hpp>

namespace HBE::Default::Components {
    /**
     * @brief Base UI element component
     * Keeps track of the type of UI element to group similar components together for one system to handle.
     */
    struct UIElement : public HBE::Core::IComponent, public HBE::Core::IMemberChanged {
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

        DEFINE_NAME("UIElement");
        UIElement() = default;
        virtual ~UIElement() = default;

        virtual void Serialize(YAML::Emitter &out) const { out << YAML::Key << "type" << YAML::Value << (int)m_type; }
        virtual void Deserialize(YAML::Node &node) {
            if (node["type"])
                m_type = (UIType)node["type"].as<int>();

            MarkDirty();
        }
    };
} // namespace HBE::Default::Components