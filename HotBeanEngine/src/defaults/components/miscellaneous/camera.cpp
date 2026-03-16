/**
 * @file camera.cpp
 * @author Daniel Parker (DParker13)
 * @brief Camera component. Used for rendering a 2D scene.
 * @version 0.1
 * @date 2026-03-15
 *
 * @copyright Copyright (c) 2026
 */

#include <HotBeanEngine/defaults/components/miscellaneous/camera.hpp>

#include <HotBeanEngine/editor/property_nodes/bool.hpp>
#include <HotBeanEngine/editor/property_nodes/float.hpp>
#include <HotBeanEngine/editor/property_nodes/vec2.hpp>

namespace HBE::Default::Components {
    using namespace Application::GUI::PropertyNodes;

    void Camera::Serialize(YAML::Emitter &out) const {
        out << YAML::Key << "active" << YAML::Value << m_active;
        out << YAML::Key << "zoom" << YAML::Value << m_zoom;
        out << YAML::Key << "layer_mask" << YAML::Value << m_layer_mask.to_string();
        out << YAML::Key << "viewport_position" << YAML::Value << m_viewport_position;
        out << YAML::Key << "viewport_size" << YAML::Value << m_viewport_size;
    }

    void Camera::Deserialize(YAML::Node &node) {
        if (node["active"]) {
            m_active = node["active"].as<bool>();
        }
        if (node["zoom"]) {
            m_zoom = node["zoom"].as<float>();
        }
        if (node["layer_mask"]) {
            m_layer_mask = string_to_bitset(node["layer_mask"].as<std::string>());
        }
        if (node["viewport_position"]) {
            m_viewport_position = node["viewport_position"].as<glm::vec2>();
        }
        if (node["viewport_size"]) {
            m_viewport_size = node["viewport_size"].as<glm::vec2>();
        }
    }

    void Camera::RenderProperties(int &id) {
        Bool::RenderProperty(id, "Active", m_active);
        Float::RenderProperty(id, "Zoom", m_zoom, 0.0f);

        ImGui::Separator();
        ImGui::Text("Viewport");
        Vec2::RenderProperty(id, "Position", m_viewport_position, {0.0f, 0.0f}, {1.0f, 1.0f});
        Vec2::RenderProperty(id, "Size", m_viewport_size, {0.0f, 0.0f}, {1.0f, 1.0f});
    }
} // namespace HBE::Default::Components