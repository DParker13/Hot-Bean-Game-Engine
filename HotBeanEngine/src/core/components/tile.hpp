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
        Uint8 _type;
        Uint8 _size;
        SDL_Vertex _vertices[4];
        SDL_Color _color;

        int _INDICES[6] = { 0, 1, 2, 1, 3, 2 };

        Tile() = default;

        std::string GetName() const override {
            return "Tile";
        }

        void Serialize(YAML::Emitter& out) const override {
            out << YAML::Key << "type" << YAML::Value << _type;
            out << YAML::Key << "size" << YAML::Value << _size;
        }

        void Deserialize(YAML::Node& node) override {
            _type = node["type"].as<Uint8>();
            _size = node["size"].as<Uint8>();
        }
    };
}