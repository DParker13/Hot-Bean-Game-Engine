#pragma once

#include <vec3.hpp>

#include "../core/ecs.hpp"

namespace Components {
    struct RigidBody : public Object {
        glm::vec3 velocity;
        glm::vec3 acceleration;
        float gravity;

        RigidBody()
        : velocity(glm::vec3(0.0f, 0.0f, 0.0f)), acceleration(glm::vec3(0.0f, 0.0f, 0.0f)), gravity(0.0f) {};

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