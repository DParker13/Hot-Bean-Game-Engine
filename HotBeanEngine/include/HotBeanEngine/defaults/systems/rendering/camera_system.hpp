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

namespace HBE::Default::Systems {
    using namespace HBE::Core;
    using namespace HBE::Default::Components;

    /**
     * @brief Manages camera positioning and view matrices
     * 
     * Updates active camera transforms for rendering.
     * Handles camera switching and viewport management.
     */
    class CameraSystem : public ISystem {
    public:
        DEFINE_SIGNATURE(CameraSystem, "Camera System", Transform2D, Camera);
        CameraSystem() = default;
        ~CameraSystem() = default;

        std::vector<EntityID> GetAllActiveCameras();
        static float GetZoom(EntityID camera_entity);
        static SDL_FRect GetViewport(EntityID camera_entity);
        static glm::vec2 GetViewportCenter(EntityID camera_entity);
        static glm::vec2 CalculateScreenPosition(EntityID camera_entity, EntityID entity);
        static bool IsCulled(EntityID camera_entity, EntityID entity);
    };
}