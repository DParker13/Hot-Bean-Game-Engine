/**
 * @file tile.hpp
 * @author Daniel Parker (DParker13)
 * @brief Tile component. Used for rendering tiles (simple rectangles).
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "../ecs/all_ecs.hpp"

namespace Components {
    struct Tile : public Component {
        Uint8 m_type;
        Uint8 m_size;
        SDL_Vertex m_vertices[4];
        SDL_Color m_color;

        int m_INDICES[6] = { 0, 1, 2, 1, 3, 2 };

        Tile() = default;

        std::string GetName() const override {
            return "Tile";
        }

        void Serialize(YAML::Emitter& out) const override {
            out << YAML::Key << "type" << YAML::Value << m_type;
            out << YAML::Key << "size" << YAML::Value << m_size;
        }

        void Deserialize(YAML::Node& node) override {
            m_type = (Uint8)node["type"].as<int>();
            m_size = (Uint8)node["size"].as<int>();
        }
    };
}