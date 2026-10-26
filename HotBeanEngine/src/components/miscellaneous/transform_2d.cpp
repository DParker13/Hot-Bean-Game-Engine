/**
 * @file transform_2d.cpp
 * @author Daniel Parker (DParker13)
 * @brief Transform 2D component. Tracks entity position, rotation, and scale.
 * @version 0.1
 * @date 2026-03-15
 *
 * @copyright Copyright (c) 2026
 */

#include <HotBeanEngine/components/miscellaneous/transform_2d.hpp>

#include <HotBeanEngine/editor/property_nodes/float.hpp>
#include <HotBeanEngine/editor/property_nodes/int.hpp>
#include <HotBeanEngine/editor/property_nodes/vec2.hpp>

namespace HBE::Components {
    using namespace Editor::PropertyNodes;

    void Transform2D::Serialize(Core::ISerializationWriter &out) const {
        out.BeginSection("Transform2D");
        if (m_layer != 0) {
            out.Write("layer", (int)m_layer);
        }
        if (m_parent != -1) {
            out.Write("parent", (int)m_parent);
        }
        if (m_local_position != glm::vec2{0.0f, 0.0f}) {
            out.Write("local_position", m_local_position);
        }
        if (m_local_rotation != 0.0f) {
            out.Write("local_rotation", m_local_rotation);
        }
        if (m_local_scale != glm::vec2{1.0f, 1.0f}) {
            out.Write("local_scale", m_local_scale);
        }
        if (m_world_position != glm::vec2{0.0f, 0.0f}) {
            out.Write("world_position", m_world_position);
        }
        if (m_world_rotation != 0.0f) {
            out.Write("world_rotation", m_world_rotation);
        }
        if (m_world_scale != glm::vec2{1.0f, 1.0f}) {
            out.Write("world_scale", m_world_scale);
        }
        out.EndSection();
    }

    void Transform2D::Deserialize(Core::ISerializationReader &in) {
        in.BeginSection("Transform2D");
        in.Read("layer", m_layer);
        in.Read("parent", m_parent);
        in.Read("local_position", m_local_position);
        in.Read("local_rotation", m_local_rotation);
        in.Read("local_scale", m_local_scale);
        in.Read("world_position", m_world_position);
        in.Read("world_rotation", m_world_rotation);
        in.Read("world_scale", m_world_scale);
        in.EndSection();

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
} // namespace HBE::Components