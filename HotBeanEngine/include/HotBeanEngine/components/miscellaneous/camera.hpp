/**
 * @file camera.hpp
 * @author Daniel Parker (DParker13)
 * @brief Camera component. Used for rendering a 2D scene.
 * @version 0.1
 * @date 2025-05-13
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <HotBeanEngine/core/all_core.hpp>
#include <HotBeanEngine/editor/iproperty_renderable.hpp>

namespace HBE::Components {
    /**
     * @brief Camera component for 2D scene rendering
     *
     * Controls viewport and layer visibility.
     * Supports multiple camera system with priority-based rendering.
     */
    struct Camera : public Core::IComponent, public GUI::IPropertyRenderable {
        bool m_active = true;
        float m_zoom = 1.0f;              /// Camera zoom level (1.0 = normal, >1.0 = zoomed in, <1.0 = zoomed out)
        std::bitset<16> m_layer_mask = 0; /// Layer visibility mask (16 layers, bitset for each layer's visibility)

        // Viewport (normalized coordinates: 0.0 to 1.0)
        glm::vec2 m_viewport_position = {0.0f,
                                         0.0f};   /// Top-left position (0,0 = top-left of screen, 1,1 = bottom-right)
        glm::vec2 m_viewport_size = {1.0f, 1.0f}; /// Size (1,1 = full screen, 0.5,0.5 = quarter screen)

        DEFINE_NAME("Camera");
        Camera() = default;

        void Serialize(Core::ISerializationWriter &out) const override;
        void Deserialize(Core::ISerializationReader &in) override;
        void RenderProperties(int &id) override;

        // Bitset
        std::bitset<16> string_to_bitset(const std::string &s) {
            assert(s.size() == 16 && "There must be 16 bits");

            return std::bitset<16>(s);
        }
    };
} // namespace HBE::Components