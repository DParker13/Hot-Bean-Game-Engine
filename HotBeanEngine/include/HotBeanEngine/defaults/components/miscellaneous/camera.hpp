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

namespace HBE::Default::Components {
    /**
     * @brief Camera component for 2D scene rendering
     * 
     * Controls viewport and layer visibility.
     * Supports multiple camera system with priority-based rendering.
     */
    struct Camera : public Component, public HBE::Application::GUI::IPropertyRenderable {
        Uint8 m_id = 0;
        bool m_active = false;
        std::bitset<16> m_layer_mask = 0;

        DEFINE_NAME("Camera");
        Camera() = default;

        void Serialize(YAML::Emitter& out) const override {
            out << YAML::Key << "id" << YAML::Value << m_id;
            out << YAML::Key << "active" << YAML::Value << m_active;
            out << YAML::Key << "layer_mask" << YAML::Value << m_layer_mask.to_string();
        }

        void Deserialize(YAML::Node& node) override {
            if (node["id"]) {
                m_id = node["id"].as<int>();
            }
            if (node["active"]) {
                m_active = node["active"].as<bool>();
            }
            if (node["layer_mask"]) {
                m_layer_mask = string_to_bitset(node["layer_mask"].as<std::string>());
            }
        }

        void RenderProperties(Entity entity, Component* component) override {
            HBE::Application::GUI::RenderProperties<Camera>(entity, component, [](Entity entity, Camera* camera) {
                int id = static_cast<int>(camera->m_id);
                HBE::Application::GUI::PropertyNodes::Int::RenderProperty(entity, "ID", id);
                camera->m_id = static_cast<Uint8>(id); // update the original value after editing

                HBE::Application::GUI::PropertyNodes::Bool::RenderProperty(entity, "Active", camera->m_active);
            });
        }
    };
}