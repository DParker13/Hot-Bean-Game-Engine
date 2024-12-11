#pragma once

#include <vec3.hpp>
#include <gtc/quaternion.hpp>
#include <string>

#include "../core/ecs.hpp"

namespace Components {
    struct Transform : public IObject {
        glm::vec3 position;
        glm::quat rotation;
        glm::vec3 scale;

        Transform()
        : position(glm::vec3(0.0f, 0.0f, 0.0f)),
          rotation(glm::quat(0.0f, 0.0f, 0.0f, 1.0f)),
          scale(glm::vec3(1.0f, 1.0f, 1.0f)) {};

        Transform(const glm::vec3 position, const glm::quat rotation, const glm::vec3 scale)
        : position(position), rotation(rotation), scale(scale) {}

        /**
         * Prints the details of the Transform component to the console.
         * The output includes the position, rotation (as a quaternion), 
         * and scale of the component in a formatted string.
         */
        void Print() const override {
            std::string str = "    Component: Transform \n";
            str += "      Position: " + std::to_string(position.x) + ", " + std::to_string(position.y) + ", " + std::to_string(position.z) + "\n";
            str += "      Rotation: " + std::to_string(rotation.x) + ", " + std::to_string(rotation.y) + ", " + std::to_string(rotation.z) + ", " + std::to_string(rotation.w) + "\n";
            str += "      Scale: " + std::to_string(scale.x) + ", " + std::to_string(scale.y) + ", " + std::to_string(scale.z) + "\n";
            std::cout << str;
        }
    };
}