/**
 * @file shape.hpp
 * @author Daniel Parker (DParker13)
 * @brief Shape component. Used for rendering a shape.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/editor_gui/iproperty_renderable.hpp>

#include <HotBeanEngine/editor_gui/property_nodes/bool.hpp>
#include <HotBeanEngine/editor_gui/property_nodes/vec2.hpp>
#include <HotBeanEngine/editor_gui/property_nodes/color.hpp>

namespace HBE::Default::Components {
    using namespace HBE::Core;
    using namespace HBE::Application::GUI;
    
    /**
     * @brief Primitive shape rendering component
     * 
     * Renders basic geometric shapes (rectangles, circles, lines).
     * Supports filled and outlined rendering modes.
     */
    struct Shape : public IComponent, public IMemberChanged, public IPropertyRenderable {
        enum class ShapeType {
            Box
        };

        ShapeType m_type = ShapeType::Box;
        glm::vec2 m_size = glm::vec2(1.0f, 1.0f);
        bool m_filled = false;
        SDL_Color m_color = {255, 255, 255, 255};

        DEFINE_NAME("Shape");
        Shape() = default;

        void Serialize(YAML::Emitter& out) const override {
            out << YAML::Key << "size" << YAML::Value << m_size;
            out << YAML::Key << "color" << YAML::Value << m_color;
        }

        void Deserialize(YAML::Node& node) override {
            m_size = node["size"].as<glm::vec2>();
            m_color = node["color"].as<SDL_Color>();
        }

        void RenderProperties(int& id) override {
            bool changed = false;

            changed |= PropertyNodes::Bool::RenderProperty(id, "Filled", m_filled);
            changed |= PropertyNodes::Vec2::RenderProperty(id, "Size", m_size, {0.0f, 0.0f});
            changed |= PropertyNodes::Color::RenderProperty(id, "Color", m_color);

            if (changed) {
                MarkDirty();
            }
        }
    };
}