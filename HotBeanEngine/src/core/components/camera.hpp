/**
 * @file camera.hpp
 * @author Daniel Parker (DParker13)
 * @brief Camera component. Used for rendering a 2D scene.
 * @version 0.1
 * @date 2025-05-13
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "../ecs/all_ecs.hpp"

namespace Components {
    struct Camera : public Component {
        Uint8 m_id = 0;
        bool m_active = false;
        std::bitset<16> m_layer_mask = 0;
        
        Camera() = default;

        std::string GetName() const override {
            return "Camera";
        }

        void Serialize(YAML::Emitter& out) const override {
            out << YAML::Key << "id" << YAML::Value << m_id;
            out << YAML::Key << "active" << YAML::Value << m_active;
            out << YAML::Key << "layer_mask" << YAML::Value << m_layer_mask.to_string();
        }

        void Deserialize(YAML::Node& node) override {
            if (node["id"]) {
                m_id = node["id"].as<int>();
            }
            if (node["active"]) {
                m_active = node["active"].as<bool>();
            }
            if (node["layer_mask"]) {
                m_layer_mask = string_to_bitset(node["layer_mask"].as<std::string>());
            }
        }
    };
}