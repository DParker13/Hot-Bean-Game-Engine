/**
 * @file rigidbody.hpp
 * @author Daniel Parker (DParker13)
 * @brief Rigidbody component. Used for 2D physics calculations.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include <box2d/box2d.h>

#include "../../core/all_core.hpp"

namespace HBE::Components {
    class RigidBody : public Component {
        public:
            float m_mass;
            b2BodyType m_type = b2BodyType::b2_kinematicBody;
            b2BodyId m_body_id; // ID of the body in the Box2D physics engine

            // --- Constructors ---
            RigidBody() = default;

            // ---- ECS ----
            std::string GetName() const override { return "RigidBody"; }

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
    };
}
