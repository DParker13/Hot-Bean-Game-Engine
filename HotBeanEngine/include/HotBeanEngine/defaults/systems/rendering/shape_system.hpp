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

using namespace HBE::Default::Components;
using namespace HBE::Application;
using namespace HBE::Core;

namespace HBE::Default::Systems {
    /**
     * @brief Renders primitive geometric shapes
     * 
     * Draws rectangles, circles, and lines to screen.
     * Processes entities with Transform2D and Shape components.
     */
    class ShapeSystem : public System {
        private:
            CameraSystem& m_camera_system;

        public:
            DEFINE_SIGNATURE(ShapeSystem, "Shape System", Transform2D, Texture, Shape);
            ShapeSystem(CameraSystem& camera_system) : System(), m_camera_system(camera_system) {}

            void OnRender() override;
            void OnEntityAdded(Entity entity) override;

        private:
            void CreateTextureForEntity(Entity entity);
    };
}