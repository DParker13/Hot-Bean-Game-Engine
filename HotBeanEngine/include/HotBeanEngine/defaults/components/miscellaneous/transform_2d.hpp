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

#include <HotBeanEngine/core/all_core.hpp>
#include <HotBeanEngine/editor/iproperty_renderable.hpp>

#include <HotBeanEngine/editor/property_nodes/vec2.hpp>
#include <HotBeanEngine/editor/property_nodes/float.hpp>
#include <HotBeanEngine/editor/property_nodes/int.hpp>

namespace HBE::Default::Components {
    using namespace HBE::Core;
    using namespace HBE::Application::GUI;

    /**
     * @brief 2D transform component for position, rotation, and scale
     * 
     * Tracks local and world-space transformations.
     * Supports hierarchical parent-child relationships.
     */
    struct Transform2D : public IComponent, public IMemberChanged, public IPropertyRenderable {
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
        Transform2D(EntityID parent_entity) : m_parent(parent_entity) {}

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

            MarkDirty();
        }

        void RenderProperties(int& id) override {
            bool changed = false;

            changed |= PropertyNodes::Int::RenderProperty(id, "Layer", reinterpret_cast<int&>(m_layer));
            changed |= PropertyNodes::Int::RenderProperty(id, "Parent", reinterpret_cast<int&>(m_parent), -1);
            ImGui::Separator();
            changed |= PropertyNodes::Vec2::RenderProperty(id, "Local Position", m_local_position);
            changed |= PropertyNodes::Float::RenderProperty(id, "Local Rotation", m_local_rotation);
            changed |= PropertyNodes::Vec2::RenderProperty(id, "Local Scale", m_local_scale);

            if (changed) {
                MarkDirty();
            }
        }
    };
}