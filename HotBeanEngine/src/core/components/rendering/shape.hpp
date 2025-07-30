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
        float m_size = 1.0;
        Uint8 m_sides = 3;
        SDL_Color m_color = {255, 255, 255, 255};

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
            m_size = node["size"].as<float>();
            m_sides = node["sides"].as<int>();
            m_color = node["color"].as<SDL_Color>();
        }
    };
}