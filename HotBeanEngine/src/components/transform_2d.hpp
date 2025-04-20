/**
 * @file transform_2d.hpp
 * @author Daniel Parker (DParker13)
 * @brief Transform 2D component. Used to keep track of entity position, rotation, and scale.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include <glm/vec2.hpp>
#include <glm/gtc/quaternion.hpp>

#include "../core/core.hpp"

namespace Components {
    struct Transform2D : public Component {
        glm::vec2 _position = glm::vec2(0.0f, 0.0f);
        glm::quat _rotation = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
        glm::vec2 _scale = glm::vec2(1.0f, 1.0f);
        Uint8 _layer = 0;

        Transform2D() {
            Component::_name = "Transform2D";
        }

        Transform2D(const glm::vec2 position, const glm::quat rotation, const glm::vec3 scale)
        : _position(position), _rotation(rotation), _scale(scale) {}

        /**
         * Prints the details of the Transform2D component to the console.
         * The output includes the position, rotation (as a quaternion), 
         * and scale of the component in a formatted string.
         */
        std::string ToString() const override {
            std::stringstream str;
            str << "    Component: Transform2D \n";
            str << "      Position: " << _position.x << ", " << _position.y << "\n";
            str << "      Rotation: " << _rotation.x << ", " << _rotation.y << ", " << _rotation.z << ", " << _rotation.w << "\n";
            str << "      Scale: " << _scale.x << ", " << _scale.y << "\n";
            
            return str.str();
        }
    };

    // void operator >> (const YAML::Node& node, Transform2D& transform) {
    //     node["position"] >> transform._position;
    //     node["rotation"] >> transform._rotation;
    //     node["scale"] >> transform._scale;
    //     node["layer"] >> transform._layer;
    // };
}