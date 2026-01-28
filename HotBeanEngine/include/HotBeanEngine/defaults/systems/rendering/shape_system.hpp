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

#include <HotBeanEngine/defaults/systems/rendering/camera_system.hpp>

namespace HBE::Default::Systems {
    using namespace HBE::Core;
    using namespace HBE::Default::Components;

    /**
     * @brief Renders primitive geometric shapes
     *
     * Draws rectangles, circles, and lines to screen.
     * Processes entities with Transform2D and Shape components.
     */
    class ShapeSystem : public ISystem {
    private:
        CameraSystem &m_camera_system;

    public:
        DEFINE_SIGNATURE(ShapeSystem, "Shape System", Transform2D, Texture, Shape);
        ShapeSystem(CameraSystem &camera_system) : m_camera_system(camera_system) {}

        void OnRender() override;
        void OnEntityAdded(EntityID entity) override;

    private:
        void CreateTextureForEntity(EntityID entity);
        bool CompareTextureAndShape(Texture &texture, Shape &shape);
    };
} // namespace HBE::Default::Systems