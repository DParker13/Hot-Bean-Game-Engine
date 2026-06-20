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
    using namespace GUI::PropertyNodes;

    void Transform2D::Serialize(Core::IComponentWriter &out) const {
        out.Write("layer", (int)m_layer);
        out.Write("parent", (int)m_parent);
        out.Write("local_position", m_local_position);
        out.Write("local_rotation", m_local_rotation);
        out.Write("local_scale", m_local_scale);
        out.Write("world_position", m_world_position);
        out.Write("world_rotation", m_world_rotation);
        out.Write("world_scale", m_world_scale);
    }

    void Transform2D::Deserialize(Core::IComponentReader &in) {
        if (in.Has("layer"))
            m_layer = (uint8_t)in.ReadInt("layer");

        if (in.Has("m_parent"))
            m_parent = (uint8_t)in.ReadInt("m_parent");

        if (in.Has("local_position"))
            m_local_position = in.ReadVec2("local_position");

        if (in.Has("local_rotation"))
            m_local_rotation = in.ReadFloat("local_rotation");

        if (in.Has("local_scale"))
            m_local_scale = in.ReadVec2("local_scale");

        if (in.Has("world_position"))
            m_world_position = in.ReadVec2("world_position");

        if (in.Has("world_rotation"))
            m_world_rotation = in.ReadFloat("world_rotation");

        if (in.Has("world_scale"))
            m_world_scale = in.ReadVec2("world_scale");

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