/**
 * @file shape.cpp
 * @author Daniel Parker (DParker13)
 * @brief Shape component. Used for rendering a shape.
 * @version 0.1
 * @date 2026-03-15
 *
 * @copyright Copyright (c) 2026
 */

#include <HotBeanEngine/components/rendering/shape.hpp>

#include <HotBeanEngine/editor/property_nodes/bool.hpp>
#include <HotBeanEngine/editor/property_nodes/color.hpp>
#include <HotBeanEngine/editor/property_nodes/vec2.hpp>

namespace HBE::Components {
    using namespace Editor::PropertyNodes;

    void Shape::Serialize(Core::ISerializationWriter &out) const {
        const bool is_default = m_size == glm::vec2{1.0f, 1.0f} && m_color.r == 255 && m_color.g == 255 &&
                                m_color.b == 255 && m_color.a == 255 && !m_filled;
        if (is_default) {
            out.WriteEmptySection("Shape");
            return;
        }

        out.BeginSection("Shape");
        if (m_size != glm::vec2{1.0f, 1.0f}) {
            out.Write("size", m_size);
        }
        if (m_color.r != 255 || m_color.g != 255 || m_color.b != 255 || m_color.a != 255) {
            out.Write("color", m_color);
        }
        if (m_filled) {
            out.Write("filled", m_filled);
        }
        out.EndSection();
    }

    void Shape::Deserialize(Core::ISerializationReader &in) {
        in.BeginSection("Shape");
        in.Read("size", m_size);
        in.Read("color", m_color);
        in.Read("filled", m_filled);
        in.EndSection();
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
} // namespace HBE::Components