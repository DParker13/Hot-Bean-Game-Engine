/**
 * @file transform_2d.hpp
 * @author Daniel Parker (DParker13)
 * @brief Transform 2D component. Tracks entity position, rotation, and scale.
 * @version 0.1
 * @date 2025-02-23
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <HotBeanEngine/core/all_core.hpp>
#include <HotBeanEngine/editor/iproperty_renderable.hpp>

namespace HBE::Default::Components {

    /**
     * @brief 2D transform component for position, rotation, and scale
     *
     * Tracks local and world-space transformations.
     * Supports hierarchical parent-child relationships.
     */
    struct Transform2D : public Core::IComponent, public Core::DirtyFlag, public Application::GUI::IPropertyRenderable {
        Uint8 m_layer = 0;
        Sint64 m_parent = -1;

        // Local transform (relative to parent)
        glm::vec2 m_local_position = {0.0f, 0.0f};
        float m_local_rotation = 0.0f; // degrees
        glm::vec2 m_local_scale = {1.0f, 1.0f};

        // World transform (computed from parent)
        glm::vec2 m_world_position = {0.0f, 0.0f};
        float m_world_rotation = 0.0f; // degrees
        glm::vec2 m_world_scale = {1.0f, 1.0f};

        DEFINE_NAME("Transform2D");
        Transform2D() = default;
        Transform2D(glm::vec2 position) : m_world_position(position) {}
        Transform2D(Core::EntityID parent_entity) : m_parent(parent_entity) {}

        void Serialize(YAML::Emitter &out) const override;
        void Deserialize(YAML::Node &node) override;
        void RenderProperties(int &id) override;
    };
} // namespace HBE::Default::Components