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

#include "../../ecs/all_ecs.hpp"

namespace Core::Components {
    struct Transform2D : public Component {
        Uint8 m_layer = 0;
        Entity m_parent = -1;

        glm::vec2 m_local_position = glm::vec2(0.0f, 0.0f);
        glm::quat m_local_rotation = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
        glm::vec2 m_local_scale = glm::vec2(1.0f, 1.0f);

        glm::vec2 m_world_position = glm::vec2(0.0f, 0.0f);
        glm::quat m_world_rotation = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
        glm::vec2 m_world_scale = glm::vec2(1.0f, 1.0f);

        glm::vec2 m_screen_position = glm::vec2(0.0f, 0.0f);
        glm::quat m_screen_rotation = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
        glm::vec2 m_screen_scale = glm::vec2(1.0f, 1.0f);

        Transform2D() = default;
        Transform2D(Entity parent) : m_parent(parent) {}

        std::string GetName() const override {
            return "Transform2D";
        }

        void Serialize(YAML::Emitter& out) const override {
            out << YAML::Key << "layer" << YAML::Value << (int)m_layer;
            out << YAML::Key << "parent" << YAML::Value << (int)m_parent;
            out << YAML::Key << "local_position" << YAML::Value << m_local_position;
            out << YAML::Key << "local_rotation" << YAML::Value << m_local_rotation;
            out << YAML::Key << "local_scale" << YAML::Value << m_local_scale;
            out << YAML::Key << "world_position" << YAML::Value << m_world_position;
            out << YAML::Key << "world_rotation" << YAML::Value << m_world_rotation;
            out << YAML::Key << "world_scale" << YAML::Value << m_world_scale;
        }

        void Deserialize(YAML::Node& node) override {
            if (node["layer"].IsDefined()) {
                m_layer = node["layer"].as<Uint8>();
            }

            if (node["parent"].IsDefined()) {
                m_parent = node["parent"].as<Uint8>();
            }
            
            if (node["local_position"].IsDefined()) {
                m_local_position = node["local_position"].as<glm::vec2>();
            }

            if (node["local_rotation"].IsDefined()) {
                m_local_rotation = node["local_rotation"].as<glm::quat>();
            }

            if (node["local_scale"].IsDefined()) {
                m_local_scale = node["local_scale"].as<glm::vec2>();
            }

            if (node["world_position"].IsDefined()) {
                m_world_position = node["world_position"].as<glm::vec2>();
            }

            if (node["world_rotation"].IsDefined()) {
                m_world_rotation = node["world_rotation"].as<glm::quat>();
            }

            if (node["world_scale"].IsDefined()) {
                m_world_scale = node["world_scale"].as<glm::vec2>();
            }
        }
    };
}