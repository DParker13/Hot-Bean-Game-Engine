/**
 * @file collider_2d.hpp
 * @author Daniel Parker (DParker13)
 * @brief Used for 2D collision detection.
 * @version 0.1
 * @date 2025-03-02
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once

#include "../../ecs/all_ecs.hpp"

namespace Core::Components {
    struct Collider2D : public Component {
        glm::vec2 _bounding_box;
        bool _is_static;
        bool _is_trigger;

        Collider2D() = default;

        std::string GetName() const override {
            return "Collider2D";
        }

        void Serialize(YAML::Emitter& out) const override {
            out << YAML::Key << "bounding_box" << YAML::Value << _bounding_box;
            out << YAML::Key << "is_static" << YAML::Value << _is_static;
            out << YAML::Key << "is_trigger" << YAML::Value << _is_trigger;
        }

        void Deserialize(YAML::Node& node) override {
            _bounding_box = node["bounding_box"].as<glm::vec2>();
            _is_static = node["is_static"].as<bool>();
            _is_trigger = node["is_trigger"].as<bool>();
        }
    };
}