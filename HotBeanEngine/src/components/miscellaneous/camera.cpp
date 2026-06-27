/**
 * @file camera.cpp
 * @author Daniel Parker (DParker13)
 * @brief Camera component. Used for rendering a 2D scene.
 * @version 0.1
 * @date 2026-03-15
 *
 * @copyright Copyright (c) 2026
 */

#include <HotBeanEngine/components/miscellaneous/camera.hpp>

#include <HotBeanEngine/editor/property_nodes/bool.hpp>
#include <HotBeanEngine/editor/property_nodes/float.hpp>
#include <HotBeanEngine/editor/property_nodes/vec2.hpp>

namespace HBE::Components {
    using namespace GUI::PropertyNodes;

    void Camera::Serialize(Core::ISerializationWriter &out) const {
        out.Write("active", m_active);
        out.Write("zoom", m_zoom);
        out.Write("layer_mask", m_layer_mask.to_string());
        out.Write("viewport_position", m_viewport_position);
        out.Write("viewport_size", m_viewport_size);
    }

    void Camera::Deserialize(Core::ISerializationReader &in) {
        in.Read("active", m_active);
        in.Read("zoom", m_zoom);

        std::string layer_mask_str;
        in.Read("layer_mask", layer_mask_str);
        if (!layer_mask_str.empty()) {
            m_layer_mask = string_to_bitset(layer_mask_str);
        }

        in.Read("viewport_position", m_viewport_position);
        in.Read("viewport_size", m_viewport_size);
    }

    void Camera::RenderProperties(int &id) {
        Bool::RenderProperty(id, "Active", m_active);
        Float::RenderProperty(id, "Zoom", m_zoom, 0.0f);

        ImGui::Separator();
        ImGui::Text("Viewport");
        Vec2::RenderProperty(id, "Position", m_viewport_position, {0.0f, 0.0f}, {1.0f, 1.0f});
        Vec2::RenderProperty(id, "Size", m_viewport_size, {0.0f, 0.0f}, {1.0f, 1.0f});
    }
} // namespace HBE::Components