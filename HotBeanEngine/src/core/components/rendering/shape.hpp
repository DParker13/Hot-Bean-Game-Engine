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

#include "../../ecs/all_ecs.hpp"

namespace Core::Components {
    struct Shape : public Component {
        enum ShapeType {
            POLYGON,
            CIRCLE
        };
        glm::vec2 m_size = glm::vec2(10.0f, 10.0f);
        Uint8 m_sides = 4;
        SDL_Color m_color = SDL_Color();
        SDL_Vertex m_vertices[4];
        int m_indices[6] = { 0, 1, 2, 1, 3, 2 };

        Shape() = default;

        std::string GetName() const override {
            return "Shape";
        }

        void Serialize(YAML::Emitter& out) const override {
            out << YAML::Key << "size" << YAML::Value << m_size;
            out << YAML::Key << "sides" << YAML::Value << m_sides;
            out << YAML::Key << "color" << YAML::Value << m_color;
        }

        void Deserialize(YAML::Node& node) override {
            m_size = node["size"].as<glm::vec2>();
            m_sides = node["sides"].as<int>();
            m_color = node["color"].as<SDL_Color>();
        }
    };
}