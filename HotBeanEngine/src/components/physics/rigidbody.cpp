/**
 * @file rigidbody.cpp
 * @author Daniel Parker (DParker13)
 * @brief Rigidbody component. Used for 2D physics calculations.
 * @version 0.1
 * @date 2026-03-15
 *
 * @copyright Copyright (c) 2026
 */

#include <HotBeanEngine/components/physics/rigidbody.hpp>

#include <HotBeanEngine/editor/property_nodes/enum.hpp>
#include <HotBeanEngine/editor/property_nodes/float.hpp>
#include <HotBeanEngine/editor/property_nodes/int.hpp>
#include <HotBeanEngine/editor/property_nodes/vec2.hpp>

namespace HBE::Components {
    using namespace GUI::PropertyNodes;

    void RigidBody::Serialize(Core::IComponentWriter &out) const {
        out.Write("mass", m_mass);
        out.Write("type", (int)m_type);
    }

    void RigidBody::Deserialize(Core::IComponentReader &in) {
        if (in.Has("mass"))
            m_mass = in.ReadFloat("mass");
        if (in.Has("type"))
            m_type = (b2BodyType)in.ReadInt("type");
    }

    void RigidBody::RenderProperties(int &id) {
        Int::RenderProperty(id, "ID", m_body_id.index1, INT_MIN, INT_MAX, true);
        Float::RenderProperty(id, "Mass", m_mass, 0.0f);
        Enum::RenderProperty<b2BodyType>(id, "Type", m_type,
                                         {{b2BodyType::b2_staticBody, "Static"},
                                          {b2BodyType::b2_kinematicBody, "Kinematic"},
                                          {b2BodyType::b2_dynamicBody, "Dynamic"}});
    }
} // namespace HBE::Components
