/**
 * @file button.hpp
 * @author Daniel Parker (DParker13)
 * @brief Button component
 * @version 0.1
 * @date 2025-25-02
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

#include <HotBeanEngine/defaults/components/ui/ui_element.hpp>
#include <HotBeanEngine/editor/iproperty_renderable.hpp>

namespace HBE::Default::Components {
    struct Button : public UIElement, public Application::GUI::IPropertyRenderable {
        bool m_mouse_hover = false; ///< Whether mouse is currently over the button
        bool m_was_hovered_last_frame =
            false; ///< Whether mouse was over the button in the last frame (used for event emission)

        DEFINE_NAME("Button");
        Button() : UIElement() {}

        void Deserialize(YAML::Node &node) override;

        void Serialize(YAML::Emitter &out) const override;

        void RenderProperties(int &id);
    };
} // namespace HBE::Default::Components