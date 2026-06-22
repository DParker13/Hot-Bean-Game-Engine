/**
 * @file interactive.hpp
 * @author Daniel Parker (DParker13)
 * @brief Interactive component
 * @version 0.1
 * @date 2026-03-17
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

#include <HotBeanEngine/core/component.hpp>
#include <HotBeanEngine/editor/iproperty_renderable.hpp>

namespace HBE::Components {
    struct Interactive : public Core::IComponent, public GUI::IPropertyRenderable {
        bool m_mouse_hover = false; /// Whether mouse is currently over the button

        DEFINE_NAME("Interactive");
        Interactive() = default;
        ~Interactive() = default;

        void Deserialize(Core::ISerializationReader &in) override;
        void Serialize(Core::ISerializationWriter &out) const override;
        void RenderProperties(int &id) override;
    };
} // namespace HBE::Components