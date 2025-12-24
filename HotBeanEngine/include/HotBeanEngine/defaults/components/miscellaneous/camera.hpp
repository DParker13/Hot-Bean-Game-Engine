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

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/editor_gui/iproperty_renderable.hpp>

#include <HotBeanEngine/editor_gui/property_nodes/int.hpp>
#include <HotBeanEngine/editor_gui/property_nodes/bool.hpp>
#include <HotBeanEngine/editor_gui/property_nodes/float.hpp>
#include <HotBeanEngine/editor_gui/property_nodes/vec2.hpp>

namespace HBE::Default::Components {
    using namespace HBE::Core;
    using namespace HBE::Application::GUI;
    
    /**
     * @brief Camera component for 2D scene rendering
     * 
     * Controls viewport and layer visibility.
     * Supports multiple camera system with priority-based rendering.
     */
    struct Camera : public IComponent, public IPropertyRenderable {
        bool m_active = true;
        float m_zoom = 1.0f; ///< Camera zoom level (1.0 = normal, >1.0 = zoomed in, <1.0 = zoomed out)
        std::bitset<16> m_layer_mask = 0; ///< Layer visibility mask (16 layers, bitset for each layer's visibility)
        
        // Viewport (normalized coordinates: 0.0 to 1.0)
        glm::vec2 m_viewport_position = {0.0f, 0.0f}; ///< Top-left position (0,0 = top-left of screen, 1,1 = bottom-right)
        glm::vec2 m_viewport_size = {1.0f, 1.0f};     ///< Size (1,1 = full screen, 0.5,0.5 = quarter screen)

        DEFINE_NAME("Camera");
        Camera() = default;

        void Serialize(YAML::Emitter& out) const override {
            out << YAML::Key << "active" << YAML::Value << m_active;
            out << YAML::Key << "zoom" << YAML::Value << m_zoom;
            out << YAML::Key << "layer_mask" << YAML::Value << m_layer_mask.to_string();
            out << YAML::Key << "viewport_position" << YAML::Value << m_viewport_position;
            out << YAML::Key << "viewport_size" << YAML::Value << m_viewport_size;
        }

        void Deserialize(YAML::Node& node) override {
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

        void RenderProperties(int& id) override {
            PropertyNodes::Bool::RenderProperty(id, "Active", m_active);
            PropertyNodes::Float::RenderProperty(id, "Zoom", m_zoom, 0.0f);
            
            ImGui::Separator();
            ImGui::Text("Viewport");
            PropertyNodes::Vec2::RenderProperty(id, "Position", m_viewport_position, {0.0f, 0.0f}, {1.0f, 1.0f});
            PropertyNodes::Vec2::RenderProperty(id, "Size", m_viewport_size, {0.0f, 0.0f}, {1.0f, 1.0f});
        }
    };
}