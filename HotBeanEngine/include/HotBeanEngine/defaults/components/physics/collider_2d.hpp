/**
 * @file collider_2d.hpp
 * @author Daniel Parker (DParker13)
 * @brief Used for 2D collision detection.
 * @version 0.1
 * @date 2025-03-02
 *
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <HotBeanEngine/core/all_core.hpp>
#include <HotBeanEngine/editor/iproperty_renderable.hpp>

#include <HotBeanEngine/editor/property_nodes/bool.hpp>
#include <HotBeanEngine/editor/property_nodes/enum.hpp>
#include <HotBeanEngine/editor/property_nodes/vec2.hpp>

namespace HBE::Default::Components {

    /**
     * @brief 2D collision shape component
     *
     * Defines collision boundaries for physics bodies.
     * Integrates with Box2D shape system.
     */
    struct Collider2D : public Core::IComponent, public Application::GUI::IPropertyRenderable {
        enum class ColliderShape { Box, Circle };

        ColliderShape m_shape = ColliderShape::Box;
        glm::vec2 m_size = {0.0f, 0.0f};
        bool m_is_trigger = false;

        DEFINE_NAME("Collider2D");
        Collider2D() = default;
        Collider2D(ColliderShape shape) : m_shape(shape) {}

        void Serialize(YAML::Emitter &out) const override;
        void Deserialize(YAML::Node &node) override;
        void RenderProperties(int &id) override;
    };
} // namespace HBE::Default::Components