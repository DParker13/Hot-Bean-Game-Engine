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

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/editor_gui/iproperty_renderable.hpp>

#include <HotBeanEngine/editor_gui/property_nodes/bool.hpp>
#include <HotBeanEngine/editor_gui/property_nodes/vec2.hpp>
#include <HotBeanEngine/editor_gui/property_nodes/enum.hpp>

namespace HBE::Default::Components {
    using namespace HBE::Core;
    
    /**
     * @brief 2D collision shape component
     * 
     * Defines collision boundaries for physics bodies.
     * Integrates with Box2D shape system.
     */
    struct Collider2D : public IComponent, public HBE::Application::GUI::IPropertyRenderable {
        enum class ColliderShape {
            Box,
            Circle
        };

        ColliderShape m_shape = ColliderShape::Box;
        glm::vec2 m_size = {0.0f, 0.0f};
        bool m_is_trigger = false;

        DEFINE_NAME("Collider2D");
        Collider2D() = default;
        Collider2D(ColliderShape shape) : m_shape(shape) {}

        void Serialize(YAML::Emitter& out) const override {
            out << YAML::Key << "bounding_box" << YAML::Value << m_size;
            out << YAML::Key << "is_trigger" << YAML::Value << m_is_trigger;
        }

        void Deserialize(YAML::Node& node) override {
            m_size = node["bounding_box"].as<glm::vec2>();
            m_is_trigger = node["is_trigger"].as<bool>();
        }

        void RenderProperties(EntityID entity, IComponent* component) override {
            auto* collider = dynamic_cast<Collider2D*>(component);

            if (!collider) {
                return;
            }

            HBE::Application::GUI::RenderProperties<Collider2D>(entity, collider, [](EntityID entity, auto* collider) {
                HBE::Application::GUI::PropertyNodes::Enum::RenderProperty<ColliderShape>(entity, "Shape", collider->m_shape, {
                    {ColliderShape::Box, "Box"},
                    {ColliderShape::Circle, "Circle"}
                });
                HBE::Application::GUI::PropertyNodes::Vec2::RenderProperty(entity, "Size", collider->m_size);
                HBE::Application::GUI::PropertyNodes::Bool::RenderProperty(entity, "Is Trigger", collider->m_is_trigger);
            });
        }
    };
}