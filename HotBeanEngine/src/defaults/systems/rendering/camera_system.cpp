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

    float CameraSystem::GetZoom(EntityID camera_entity) {
        if (!g_ecs.HasComponent<Camera>(camera_entity)) {
            LOG(LoggingType::WARNING, "Entity does not have a Camera component!");
            return 1.0f;
        }

        const Camera &camera = g_ecs.GetComponent<Camera>(camera_entity);
        return camera.m_zoom;
    }

    SDL_FRect CameraSystem::GetViewport(EntityID camera_entity) {
        // Get screen dimensions
        int screen_width, screen_height;
        SDL_GetRenderOutputSize(g_app.GetRenderer(), &screen_width, &screen_height);

        // Return full screen if no active camera
        if (!g_ecs.HasComponent<Camera>(camera_entity)) {
            LOG(LoggingType::WARNING, "No active camera found!");
            return SDL_FRect{0.0f, 0.0f, static_cast<float>(screen_width), static_cast<float>(screen_height)};
        }

        const Camera &camera = g_ecs.GetComponent<Camera>(camera_entity);

        // Convert normalized viewport coordinates to pixel coordinates
        return SDL_FRect{camera.m_viewport_position.x * screen_width, camera.m_viewport_position.y * screen_height,
                         camera.m_viewport_size.x * screen_width, camera.m_viewport_size.y * screen_height};
    }

    glm::vec2 CameraSystem::GetViewportCenter(EntityID camera_entity) {
        SDL_FRect viewport = GetViewport(camera_entity);
        return glm::vec2(viewport.x + viewport.w * 0.5f, viewport.y + viewport.h * 0.5f);
    }

    std::vector<EntityID> CameraSystem::GetAllActiveCameras() {
        std::vector<EntityID> active_cameras;

        for (EntityID entity : m_entities) {
            const auto &camera = g_ecs.GetComponent<Camera>(entity);

            if (camera.m_active) {
                active_cameras.push_back(entity);
            }
        }

        return active_cameras;
    }

    glm::vec2 CameraSystem::CalculateScreenPosition(EntityID camera_entity, EntityID entity) {
        // Return world position if camera is not active camera
        if (!g_ecs.HasComponent<Camera>(camera_entity)) {
            LOG(LoggingType::WARNING, "Camera entity does not have a Camera component!");
            if (!g_ecs.HasComponent<Transform2D>(entity)) {
                return {0.0f, 0.0f};
            }

            Transform2D &transform = g_ecs.GetComponent<Transform2D>(entity);
            return transform.m_world_position;
        }

        const Camera &camera = g_ecs.GetComponent<Camera>(camera_entity);
        const Transform2D &camera_transform = g_ecs.GetComponent<Transform2D>(camera_entity);
        Transform2D &transform = g_ecs.GetComponent<Transform2D>(entity);

        // Get viewport center (handles split-screen, minimaps, etc.)
        glm::vec2 viewport_center = GetViewportCenter(camera_entity);

        // Calculate position relative to camera and apply zoom
        glm::vec2 relative_position = transform.m_world_position - camera_transform.m_world_position;
        glm::vec2 zoomed_position = relative_position * camera.m_zoom;

        // Offset so camera is at viewport center
        glm::vec2 screen_position = zoomed_position + viewport_center;

        return screen_position;
    }

    /**
     * @brief Determines if a texture at a given screen position is outside the viewport bounds and should be culled
     * @param screen_position The position on the screen to check for culling
     * @param texture The texture to check for culling
     */
    bool CameraSystem::IsCulled(EntityID camera_entity, EntityID entity) {
        Texture &texture = g_ecs.GetComponent<Texture>(entity);

        glm::vec2 screen_position = CalculateScreenPosition(camera_entity, entity);

        // Get camera zoom and apply to texture size for culling check
        float zoom = GetZoom(camera_entity);
        glm::vec2 scaled_size = texture.m_size * zoom;

        // Get viewport bounds (not full screen bounds)
        SDL_FRect viewport = GetViewport(camera_entity);

        float viewport_right = viewport.x + viewport.w;
        float viewport_bottom = viewport.y + viewport.h;

        // Cull if outside viewport bounds
        return screen_position.x + scaled_size.x <= viewport.x || screen_position.y + scaled_size.y <= viewport.y ||
               screen_position.x >= viewport_right || screen_position.y >= viewport_bottom;
    }
} // namespace HBE::Default::Systems