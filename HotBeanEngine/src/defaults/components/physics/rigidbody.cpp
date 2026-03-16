/**
 * @file rigidbody.cpp
 * @author Daniel Parker (DParker13)
 * @brief Rigidbody component. Used for 2D physics calculations.
 * @version 0.1
 * @date 2026-03-15
 *
 * @copyright Copyright (c) 2026
 */

#include <HotBeanEngine/defaults/components/physics/rigidbody.hpp>

#include <HotBeanEngine/editor/property_nodes/enum.hpp>
#include <HotBeanEngine/editor/property_nodes/float.hpp>
#include <HotBeanEngine/editor/property_nodes/int.hpp>
#include <HotBeanEngine/editor/property_nodes/vec2.hpp>

namespace HBE::Default::Components {
    using namespace Application::GUI::PropertyNodes;

    void RigidBody::Serialize(YAML::Emitter &out) const {
        out << YAML::Key << "mass" << YAML::Value << m_mass;
        out << YAML::Key << "type" << YAML::Value << (int)m_type;
    }

    void RigidBody::Deserialize(YAML::Node &node) {
        if (node["mass"])
            m_mass = node["mass"].as<float>();
        if (node["type"])
            m_type = (b2BodyType)node["type"].as<int>();
    }

    void RigidBody::RenderProperties(int &id) {
        Int::RenderProperty(id, "ID", m_body_id.index1, INT_MIN, INT_MAX, true);
        Float::RenderProperty(id, "Mass", m_mass, 0.0f);
        Enum::RenderProperty<b2BodyType>(id, "Type", m_type,
                                         {{b2BodyType::b2_staticBody, "Static"},
                                          {b2BodyType::b2_kinematicBody, "Kinematic"},
                                          {b2BodyType::b2_dynamicBody, "Dynamic"}});
    }
} // namespace HBE::Default::Components
