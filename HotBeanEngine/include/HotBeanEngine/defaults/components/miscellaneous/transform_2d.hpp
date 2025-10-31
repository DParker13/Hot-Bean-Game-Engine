/**
 * @file transform_2d.hpp
 * @author Daniel Parker (DParker13)
 * @brief Transform 2D component. Tracks entity position, rotation, and scale.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/editor_gui/iproperty_renderable.hpp>

#include <HotBeanEngine/editor_gui/property_nodes/vec2.hpp>
#include <HotBeanEngine/editor_gui/property_nodes/float.hpp>
#include <HotBeanEngine/editor_gui/property_nodes/int.hpp>

namespace HBE::Default::Components {

    /**
     * @brief 2D transform component for position, rotation, and scale
     * 
     * Tracks local and world-space transformations.
     * Supports hierarchical parent-child relationships.
     */
    struct Transform2D : public Component, public HBE::Application::GUI::IPropertyRenderable {
        Uint8 m_layer = 0;
        Sint64 m_parent = -1;

        // Local transform (relative to parent)
        glm::vec2 m_local_position = {0.0f, 0.0f};
        float m_local_rotation = 0.0f;      // degrees
        glm::vec2 m_local_scale = {1.0f, 1.0f};

        // World transform (computed from parent)
        glm::vec2 m_world_position = {0.0f, 0.0f};
        float m_world_rotation = 0.0f;      // degrees
        glm::vec2 m_world_scale = {1.0f, 1.0f};

        DEFINE_NAME("Transform2D");
        Transform2D() = default;
        Transform2D(glm::vec2 position) : m_world_position(position) {}
        Transform2D(Entity m_parent_entity) : m_parent(m_parent_entity) {}

        void Serialize(YAML::Emitter& out) const override {
            out << YAML::Key << "layer" << YAML::Value << (int)m_layer;
            out << YAML::Key << "parent" << YAML::Value << (int)m_parent;
            out << YAML::Key << "local_position" << YAML::Value << m_local_position;
            out << YAML::Key << "local_rotation" << YAML::Value << m_local_rotation;
            out << YAML::Key << "local_scale" << YAML::Value << m_local_scale;
            out << YAML::Key << "world_position" << YAML::Value << m_world_position;
            out << YAML::Key << "world_rotation" << YAML::Value << m_world_rotation;
            out << YAML::Key << "world_scale" << YAML::Value << m_world_scale;
        }

        void Deserialize(YAML::Node& node) override {
            if (node["layer"].IsDefined())
                m_layer = node["layer"].as<Uint8>();

            if (node["m_parent"].IsDefined())
                m_parent = node["m_parent"].as<Uint8>();

            if (node["local_position"].IsDefined())
                m_local_position = node["local_position"].as<glm::vec2>();

            if (node["local_rotation"].IsDefined())
                m_local_rotation = node["local_rotation"].as<float>();

            if (node["local_scale"].IsDefined())
                m_local_scale = node["local_scale"].as<glm::vec2>();

            if (node["world_position"].IsDefined())
                m_world_position = node["world_position"].as<glm::vec2>();

            if (node["world_rotation"].IsDefined())
                m_world_rotation = node["world_rotation"].as<float>();

            if (node["world_scale"].IsDefined())
                m_world_scale = node["world_scale"].as<glm::vec2>();
        }

        void RenderProperties(Entity entity, Component* component) override {
            auto* transform = dynamic_cast<Transform2D*>(component);

            if (!transform) {
                return;
            }

            HBE::Application::GUI::RenderProperties<Transform2D>(entity, transform, [](Entity entity, auto* transform) {
                int layer = static_cast<int>(transform->m_layer);
                HBE::Application::GUI::PropertyNodes::Int::RenderProperty(entity, "Layer", layer);
                transform->m_layer = static_cast<Uint8>(layer); // update the original value after editing
                
                int parent = static_cast<int>(transform->m_parent);
                HBE::Application::GUI::PropertyNodes::Int::RenderProperty(entity, "Parent", parent);
                transform->m_parent = static_cast<Sint64>(parent); // update the original value after editing

                ImGui::Separator();
                HBE::Application::GUI::PropertyNodes::Vec2::RenderProperty(entity, "Local Position", transform->m_local_position);
                HBE::Application::GUI::PropertyNodes::Float::RenderProperty(entity, "Local Rotation", transform->m_local_rotation);
                HBE::Application::GUI::PropertyNodes::Vec2::RenderProperty(entity, "Local Scale", transform->m_local_scale);
            });
        }
    };
}