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

#include <glm/vec3.hpp>

#include "../core/core.hpp"

namespace Components {
    struct RigidBody : public Component {
        glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
        float gravity = -9.8f;

        RigidBody() {
            Component::_name = "RigidBody";
        }

        RigidBody(const glm::vec3 velocity, const glm::vec3 acceleration, float gravity)
        : velocity(velocity), acceleration(acceleration), gravity(gravity) {}

        /**
         * Prints the details of the Rigidbody component to the console.
         * The output includes the velocity and acceleration of the component in a formatted string.
         */
        std::string ToString() const override {
            std::string str = "    Component: Rigidbody \n";
            str += "      Velocity: " + std::to_string(velocity.x) + ", " + std::to_string(velocity.y) + ", " + std::to_string(velocity.z) + "\n";
            str += "      Acceleration: " + std::to_string(acceleration.x) + ", " + std::to_string(acceleration.y) + ", " + std::to_string(acceleration.z) + "\n";
            return str;
        }
    };
}