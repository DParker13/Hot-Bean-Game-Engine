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

#include "../ecs/all_ecs.hpp"

namespace Components {
    struct Transform2D : public Component {
        glm::vec2 _position = glm::vec2(0.0f, 0.0f);
        glm::quat _rotation = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
        glm::vec2 _scale = glm::vec2(1.0f, 1.0f);
        Uint8 _layer = 0;

        Transform2D() = default;

        Transform2D(const glm::vec2 position, const glm::quat rotation, const glm::vec3 scale)
        : _position(position), _rotation(rotation), _scale(scale) {}

        std::string GetName() const override {
            return "Transform2D";
        }

        void Serialize(YAML::Emitter& out) const override {
            out << YAML::Key << "position" << YAML::Value << _position;
            out << YAML::Key << "rotation" << YAML::Value << _rotation;
            out << YAML::Key << "scale" << YAML::Value << _scale;
            out << YAML::Key << "layer" << YAML::Value << (int)_layer;
        }

        void Deserialize(YAML::Node& node) override {
            _position = node["position"].as<glm::vec2>();
            _rotation = node["rotation"].as<glm::quat>();
            _scale = node["scale"].as<glm::vec2>();
            _layer = node["layer"].as<Uint8>();
        }
    };
}