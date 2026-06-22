/**
 * @file collider_2d.cpp
 * @author Daniel Parker (DParker13)
 * @brief Used for 2D collision detection.
 * @version 0.1
 * @date 2026-03-15
 *
 * @copyright Copyright (c) 2026
 */

#include <HotBeanEngine/components/physics/collider_2d.hpp>

namespace HBE::Components {
    using namespace GUI::PropertyNodes;

    void Collider2D::Serialize(Core::ISerializationWriter &out) const {
        out.Write("bounding_box", m_size);
        out.Write("is_trigger", m_is_trigger);
    }

    void Collider2D::Deserialize(Core::ISerializationReader &in) {
        if (in.Has("bounding_box")) {
            m_size = in.ReadVec2("bounding_box");
        }
        if (in.Has("is_trigger")) {
            m_is_trigger = in.ReadBool("is_trigger");
        }
    }

    void Collider2D::RenderProperties(int &id) {
        Enum::RenderProperty<ColliderShape>(id, "Shape", m_shape,
                                            {{ColliderShape::Box, "Box"}, {ColliderShape::Circle, "Circle"}});
        Vec2::RenderProperty(id, "Size", m_size);
        Bool::RenderProperty(id, "Is Trigger", m_is_trigger);
    }
} // namespace HBE::Components