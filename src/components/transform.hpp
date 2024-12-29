#pragma once

#include <vec3.hpp>
#include <gtc/quaternion.hpp>
#include <string>

#include "../core/ecs.hpp"

namespace Components {
    struct Transform : public Object {
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
        std::string ToString() const override {
            std::stringstream str;
            str << "    Component: Transform \n";
            str << "      Position: " << position.x << ", " << position.y << ", " << position.z << "\n";
            str << "      Rotation: " << rotation.x << ", " << rotation.y << ", " << rotation.z << ", " << rotation.w << "\n";
            str << "      Scale: " << scale.x << ", " << scale.y << ", " << scale.z << "\n";
            
            return str.str();
        }
    };
}