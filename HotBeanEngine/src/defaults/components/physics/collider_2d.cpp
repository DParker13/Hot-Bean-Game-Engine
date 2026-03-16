/**
 * @file collider_2d.cpp
 * @author Daniel Parker (DParker13)
 * @brief Used for 2D collision detection.
 * @version 0.1
 * @date 2026-03-15
 *
 * @copyright Copyright (c) 2026
 */

#include <HotBeanEngine/defaults/components/physics/collider_2d.hpp>

namespace HBE::Default::Components {
    using namespace Application::GUI::PropertyNodes;

    void Collider2D::Serialize(YAML::Emitter &out) const {
        out << YAML::Key << "bounding_box" << YAML::Value << m_size;
        out << YAML::Key << "is_trigger" << YAML::Value << m_is_trigger;
    }

    void Collider2D::Deserialize(YAML::Node &node) {
        m_size = node["bounding_box"].as<glm::vec2>();
        m_is_trigger = node["is_trigger"].as<bool>();
    }

    void Collider2D::RenderProperties(int &id) {
        Enum::RenderProperty<ColliderShape>(id, "Shape", m_shape,
                                            {{ColliderShape::Box, "Box"}, {ColliderShape::Circle, "Circle"}});
        Vec2::RenderProperty(id, "Size", m_size);
        Bool::RenderProperty(id, "Is Trigger", m_is_trigger);
    }
} // namespace HBE::Default::Components