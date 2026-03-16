/**
 * @file transform_2d.cpp
 * @author Daniel Parker (DParker13)
 * @brief Transform 2D component. Tracks entity position, rotation, and scale.
 * @version 0.1
 * @date 2026-03-15
 *
 * @copyright Copyright (c) 2026
 */

#include <HotBeanEngine/defaults/components/miscellaneous/transform_2d.hpp>

#include <HotBeanEngine/editor/property_nodes/float.hpp>
#include <HotBeanEngine/editor/property_nodes/int.hpp>
#include <HotBeanEngine/editor/property_nodes/vec2.hpp>

namespace HBE::Default::Components {
    using namespace Application::GUI::PropertyNodes;

    void Transform2D::Serialize(YAML::Emitter &out) const {
        out << YAML::Key << "layer" << YAML::Value << (int)m_layer;
        out << YAML::Key << "parent" << YAML::Value << (int)m_parent;
        out << YAML::Key << "local_position" << YAML::Value << m_local_position;
        out << YAML::Key << "local_rotation" << YAML::Value << m_local_rotation;
        out << YAML::Key << "local_scale" << YAML::Value << m_local_scale;
        out << YAML::Key << "world_position" << YAML::Value << m_world_position;
        out << YAML::Key << "world_rotation" << YAML::Value << m_world_rotation;
        out << YAML::Key << "world_scale" << YAML::Value << m_world_scale;
    }

    void Transform2D::Deserialize(YAML::Node &node) {
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

    void Transform2D::RenderProperties(int &id) {
        bool changed = false;

        changed |= Int::RenderProperty(id, "Layer", reinterpret_cast<int &>(m_layer));
        changed |= Int::RenderProperty(id, "Parent", reinterpret_cast<int &>(m_parent), -1);
        ImGui::Separator();
        changed |= Vec2::RenderProperty(id, "Local Position", m_local_position);
        changed |= Float::RenderProperty(id, "Local Rotation", m_local_rotation);
        changed |= Vec2::RenderProperty(id, "Local Scale", m_local_scale);

        if (changed) {
            MarkDirty();
        }
    }
} // namespace HBE::Default::Components