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
    using namespace GUI::PropertyNodes;

    void Shape::Serialize(Core::ISerializationWriter &out) const {
        out.Write("size", m_size);
        out.Write("color", m_color);
        out.Write("filled", m_filled);
    }

    void Shape::Deserialize(Core::ISerializationReader &in) {
        in.Read("size", m_size);
        in.Read("color", m_color);
        in.Read("filled", m_filled);
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