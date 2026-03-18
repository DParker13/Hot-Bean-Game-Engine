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

#include <HotBeanEngine/core/all_core.hpp>
#include <HotBeanEngine/editor/iproperty_renderable.hpp>

namespace HBE::Default::Components {

    /**
     * @brief Primitive shape rendering component
     *
     * Renders basic geometric shapes (rectangles, circles, lines).
     * Supports filled and outlined rendering modes.
     */
    struct Shape : public Core::IComponent, public Core::DirtyFlag, public Application::GUI::IPropertyRenderable {
        enum class ShapeType { Box };

        ShapeType m_type = ShapeType::Box;
        glm::vec2 m_size = glm::vec2(1.0f, 1.0f);
        bool m_filled = false;
        SDL_Color m_color = {255, 255, 255, 255};

        DEFINE_NAME("Shape");
        Shape() = default;

        void Serialize(YAML::Emitter &out) const override;
        void Deserialize(YAML::Node &node) override;
        void RenderProperties(int &id) override;
    };
} // namespace HBE::Default::Components