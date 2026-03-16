/**
 * @file shape.cpp
 * @author Daniel Parker (DParker13)
 * @brief Shape component. Used for rendering a shape.
 * @version 0.1
 * @date 2026-03-15
 *
 * @copyright Copyright (c) 2026
 */

#include <HotBeanEngine/defaults/components/rendering/shape.hpp>

#include <HotBeanEngine/editor/property_nodes/bool.hpp>
#include <HotBeanEngine/editor/property_nodes/color.hpp>
#include <HotBeanEngine/editor/property_nodes/vec2.hpp>

namespace HBE::Default::Components {
    using namespace Application::GUI::PropertyNodes;

    void Shape::Serialize(YAML::Emitter &out) const {
        out << YAML::Key << "size" << YAML::Value << m_size;
        out << YAML::Key << "color" << YAML::Value << m_color;
    }

    void Shape::Deserialize(YAML::Node &node) {
        m_size = node["size"].as<glm::vec2>();
        m_color = node["color"].as<SDL_Color>();
    }

    void Shape::RenderProperties(int &id) {
        bool changed = false;

        changed |= Bool::RenderProperty(id, "Filled", m_filled);
        changed |= Vec2::RenderProperty(id, "Size", m_size, {0.0f, 0.0f});
        changed |= Color::RenderProperty(id, "Color", m_color);

        if (changed) {
            MarkDirty();
        }
    }
} // namespace HBE::Default::Components