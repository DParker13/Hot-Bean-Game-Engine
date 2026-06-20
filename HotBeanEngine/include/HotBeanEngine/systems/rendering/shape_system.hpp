/**
 * @file shape_system.hpp
 * @author Daniel Parker (DParker13)
 * @brief System for 2D basic shape rendering.
 * @version 0.1
 * @date 2025-03-02
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <HotBeanEngine/components/miscellaneous/transform_2d.hpp>
#include <HotBeanEngine/components/rendering/shape.hpp>
#include <HotBeanEngine/components/rendering/texture.hpp>
#include <HotBeanEngine/core/system.hpp>

namespace HBE::Systems {
    using Components::Shape;
    using Components::Texture;
    using Components::Transform2D;
    using Core::EntityID;

    // Forward declaration
    class CameraSystem;

    /**
     * @brief Renders primitive geometric shapes
     *
     * Draws rectangles, circles, and lines to screen.
     * Processes entities with Transform2D and Shape components.
     */
    class ShapeSystem : public Core::GameSystem<Transform2D, Texture, Shape> {
    public:
        DEFINE_NAME("Shape System")

    public:
        ShapeSystem() = default;

        void OnRender() override;
        void OnEntityAdded(EntityID entity) override;

    private:
        void CreateTextureForEntity(EntityID entity);
        bool CompareTextureAndShape(Texture &texture, Shape &shape);
    };
} // namespace HBE::Systems