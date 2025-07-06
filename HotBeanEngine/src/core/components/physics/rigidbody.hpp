/**
 * @file rigidbody.hpp
 * @author Daniel Parker (DParker13)
 * @brief Rigidbody component. Used for physics calculations.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "../../ecs/all_ecs.hpp"

namespace Core::Components {
    struct RigidBody : public Component {
        glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
        float gravity = -9.8f;

        RigidBody() = default;

        std::string GetName() const override {
            return "RigidBody";
        }

        void Serialize(YAML::Emitter& out) const override {
            out << YAML::Key << "velocity" << YAML::Value << velocity;
            out << YAML::Key << "acceleration" << YAML::Value << acceleration;
            out << YAML::Key << "gravity" << YAML::Value << gravity;
        }

        void Deserialize(YAML::Node& node) override {
            velocity = node["velocity"].as<glm::vec3>();
            acceleration = node["acceleration"].as<glm::vec3>();
            gravity = node["gravity"].as<float>();
        }
    };
}