/**
 * @file ui_element.cpp
 * @author Daniel Parker (DParker13)
 * @brief UI element component. Used for rendering UI elements.
 * @version 0.1
 * @date 2026-03-15
 *
 * @copyright Copyright (c) 2026
 */

#include <HotBeanEngine/defaults/components/ui/ui_element.hpp>

namespace HBE::Default::Components {
    void UIElement::Serialize(YAML::Emitter &out) const { out << YAML::Key << "type" << YAML::Value << (int)m_type; }

    void UIElement::Deserialize(YAML::Node &node) {
        if (node["type"])
            m_type = (UIType)node["type"].as<int>();

        MarkDirty();
    }
} // namespace HBE::Default::Components