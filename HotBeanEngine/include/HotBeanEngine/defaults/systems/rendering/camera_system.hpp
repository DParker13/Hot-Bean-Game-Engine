/**
 * @file camera_system.hpp
 * @author Daniel Parker (DParker13)
 * @brief System for 2D camera management.
 * @version 0.1
 * @date 2025-03-02
 * 
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/defaults/components/default_components.hpp>

using namespace HBE::Default::Components;
using namespace HBE::Application;
using namespace HBE::Core;

namespace HBE::Default::Systems {
    /**
     * @brief Manages camera positioning and view matrices
     * 
     * Updates active camera transforms for rendering.
     * Handles camera switching and viewport management.
     */
    class CameraSystem : public System {
        private:
            Sint64 m_active_camera_entity = -1;

        public:
            DEFINE_SIGNATURE(CameraSystem, "Camera System", Transform2D, Camera);
            CameraSystem() = default;
            ~CameraSystem() = default;

            void OnStart() override;
            void OnUpdate() override;

            Entity GetActiveCameraEntity();
            glm::vec2 CalculateScreenPosition(const glm::vec2& world_position);

        private:
            void FindActiveCamera();
    };
}