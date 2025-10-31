/**
 * @file rigidbody.hpp
 * @author Daniel Parker (DParker13)
 * @brief Rigidbody component. Used for 2D physics calculations.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <box2d/box2d.h>

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/editor_gui/iproperty_renderable.hpp>

#include <HotBeanEngine/editor_gui/property_nodes/int.hpp>
#include <HotBeanEngine/editor_gui/property_nodes/float.hpp>
#include <HotBeanEngine/editor_gui/property_nodes/vec2.hpp>
#include <HotBeanEngine/editor_gui/property_nodes/enum.hpp>

namespace HBE::Default::Components {
    /**
     * @brief Physics body component for 2D dynamics
     * 
     * Integrates with Box2D physics engine.
     * Handles mass, velocity, and collision response.
     */
    class RigidBody : public Component, public HBE::Application::GUI::IPropertyRenderable {
        public:
            float m_mass = 1.0f;
            b2BodyType m_type = b2BodyType::b2_kinematicBody;
            b2BodyId m_body_id = b2BodyId(); // ID of the body in the Box2D physics engine

            DEFINE_NAME("RigidBody");
            RigidBody() = default;

            void Serialize(YAML::Emitter& out) const override {
                out << YAML::Key << "mass" << YAML::Value << m_mass;
                out << YAML::Key << "type" << YAML::Value << (int)m_type;
            }

            void Deserialize(YAML::Node& node) override {
                if (node["mass"])
                    m_mass = node["mass"].as<float>();
                if (node["type"])
                    m_type = (b2BodyType)node["type"].as<int>();
            }

            void RenderProperties(Entity entity, Component* component) override {
                auto* rigidbody = dynamic_cast<RigidBody*>(component);

                if (!rigidbody) {
                    return;
                }

                HBE::Application::GUI::RenderProperties<RigidBody>(entity, rigidbody, [](Entity entity, auto* rb) {
                    HBE::Application::GUI::PropertyNodes::Int::RenderProperty(entity, "ID", rb->m_body_id.index1);
                    HBE::Application::GUI::PropertyNodes::Float::RenderProperty(entity, "Mass", rb->m_mass);
                    HBE::Application::GUI::PropertyNodes::Enum::RenderProperty<b2BodyType>(entity, "Type", rb->m_type, {
                        {b2BodyType::b2_staticBody, "Static"},
                        {b2BodyType::b2_kinematicBody, "Kinematic"},
                        {b2BodyType::b2_dynamicBody, "Dynamic"}
                    });
                });
            }
    };
}
