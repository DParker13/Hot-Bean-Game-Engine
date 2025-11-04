/**
 * @file camera_system.cpp
 * @author Daniel Parker (DParker13)
 * @brief System for offsetting all transforms based on the active camera. Only one camera can be active at a time.
 * @version 0.1
 * @date 2025-05-14
 * 
 * @copyright Copyright (c) 2025
 */

#include <HotBeanEngine/defaults/systems/rendering/camera_system.hpp>

namespace HBE::Default::Systems {
    void CameraSystem::OnStart() {
        FindActiveCamera();
    }

    void CameraSystem::OnUpdate() {
        // Validate that we have an active camera
        if (m_active_camera_entity == -1) {
            FindActiveCamera();
            return;
        }

        // Check if current camera is still valid and active
        const Camera& camera = g_ecs.GetComponent<Camera>(m_active_camera_entity);
        if (!camera.m_active) {
            FindActiveCamera();
        }
    }

    EntityID CameraSystem::GetActiveCameraEntity() {
        return m_active_camera_entity;
    }

    float CameraSystem::GetActiveZoom() const {
        // Return 1.0 (no zoom) if no active camera
        if (m_active_camera_entity == -1) {
            return 1.0f;
        }

        const Camera& camera = g_ecs.GetComponent<Camera>(m_active_camera_entity);
        return camera.m_zoom;
    }

    SDL_FRect CameraSystem::GetActiveViewport() const {
        // Get screen dimensions
        int screen_width, screen_height;
        SDL_GetRenderOutputSize(g_app.GetRenderer(), &screen_width, &screen_height);

        // Return full screen if no active camera
        if (m_active_camera_entity == -1) {
            return SDL_FRect{0.0f, 0.0f, static_cast<float>(screen_width), static_cast<float>(screen_height)};
        }

        const Camera& camera = g_ecs.GetComponent<Camera>(m_active_camera_entity);
        
        // Convert normalized viewport coordinates to pixel coordinates
        return SDL_FRect{
            camera.m_viewport_position.x * screen_width,
            camera.m_viewport_position.y * screen_height,
            camera.m_viewport_size.x * screen_width,
            camera.m_viewport_size.y * screen_height
        };
    }

    glm::vec2 CameraSystem::GetViewportCenter() const {
        SDL_FRect viewport = GetActiveViewport();
        return glm::vec2(
            viewport.x + viewport.w * 0.5f,
            viewport.y + viewport.h * 0.5f
        );
    }

    void CameraSystem::FindActiveCamera() {
        bool first_camera_found = false;
        m_active_camera_entity = -1; // Reset before searching

        for (auto& entity : m_entities) {
            const auto& camera = g_ecs.GetComponent<Camera>(entity);

            if (camera.m_active) {
                if (first_camera_found) {
                    LOG(LoggingType::WARNING, "More than one camera is active! Using first found.");
                } else {
                    first_camera_found = true;
                    m_active_camera_entity = static_cast<Sint64>(entity);
                }
            }
        }

        if (!first_camera_found) {
            LOG(LoggingType::WARNING, "No active cameras found!");
            m_active_camera_entity = -1;
        }
    }

    glm::vec2 CameraSystem::CalculateScreenPosition(const glm::vec2& world_position) {
        // Return world position as-is if no active camera
        if (m_active_camera_entity == -1) {
            return world_position;
        }

        const Camera& camera = g_ecs.GetComponent<Camera>(m_active_camera_entity);
        const Transform2D& camera_transform = g_ecs.GetComponent<Transform2D>(m_active_camera_entity);
        
        // Get viewport center (handles split-screen, minimaps, etc.)
        glm::vec2 viewport_center = GetViewportCenter();
        
        // Calculate position relative to camera and apply zoom
        // Then offset so camera is at viewport center
        glm::vec2 screen_position = (world_position - camera_transform.m_world_position) * camera.m_zoom + viewport_center;

        return screen_position;
    }
}