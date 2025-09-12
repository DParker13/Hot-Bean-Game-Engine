/**
 * @file shape.hpp
 * @author Daniel Parker (DParker13)
 * @brief Shape component. Used for rendering a box.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "../../core/all_core.hpp"

namespace HBE::Components {
    struct Shape : public Component {
        enum class ShapeType {
            Box
        };

        ShapeType m_type = ShapeType::Box;
        glm::vec2 m_size = glm::vec2(1.0f, 1.0f);
        bool m_filled = false;
        SDL_Color m_color = {255, 255, 255, 255};

        Shape() = default;

        std::string GetName() const override {
            return "Shape";
        }

        void Serialize(YAML::Emitter& out) const override {
            out << YAML::Key << "size" << YAML::Value << m_size;
            out << YAML::Key << "color" << YAML::Value << m_color;
        }

        void Deserialize(YAML::Node& node) override {
            m_size = node["size"].as<glm::vec2>();
            m_color = node["color"].as<SDL_Color>();
        }
    };
}