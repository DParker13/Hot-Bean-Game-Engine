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

#include "../../core/all_core.hpp"

namespace HBE::Components {
    struct Collider2D : public Component {
        enum class ColliderShape {
            Square,
            Circle // TODO: Implement collision detection for this shape
        };

        ColliderShape m_shape = ColliderShape::Square;
        glm::vec2 m_size;
        bool m_is_trigger = false;

        Collider2D() = default;
        Collider2D(ColliderShape shape) : m_shape(shape) {}

        std::string GetName() const override {
            return "Collider2D";
        }

        void Serialize(YAML::Emitter& out) const override {
            out << YAML::Key << "bounding_box" << YAML::Value << m_size;
            out << YAML::Key << "is_trigger" << YAML::Value << m_is_trigger;
        }

        void Deserialize(YAML::Node& node) override {
            m_size = node["bounding_box"].as<glm::vec2>();
            m_is_trigger = node["is_trigger"].as<bool>();
        }
    };
}