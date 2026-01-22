/**
 * @file editor_camera.cpp
 * @author Daniel Parker (DParker13)
 * @brief System for offsetting all transforms based on the editor camera.
 * @version 0.1
 * @date 2025-12-29
 * 
 * @copyright Copyright (c) 2025
 */

#include <HotBeanEngine/editor_gui/editor_camera.hpp>

namespace HBE::Application::GUI {
    SDL_FRect EditorCamera::GetViewport() {
        // // Get screen dimensions
        // int screen_width, screen_height;
        // SDL_GetRenderOutputSize(g_app.GetRenderer(), &screen_width, &screen_height);

        // // Convert normalized viewport coordinates to pixel coordinates
        // return SDL_FRect{
        //     m_camera.x,
        //     m_camera.y,
        //     (float)screen_width,
        //     (float)screen_height
        // };
        return SDL_FRect{0.0f, 0.0f, 1920.0f, 1080.0f};
    }

    glm::vec2 EditorCamera::GetViewportCenter() {
        SDL_FRect viewport = GetViewport();
        return glm::vec2(
            viewport.x + viewport.w * 0.5f,
            viewport.y + viewport.h * 0.5f
        );
    }

    glm::vec2 EditorCamera::CalculateScreenPosition(EntityID entity) {
        // Return world position if m_camera is not active m_camera
        // if (!g_ecs.HasComponent<Transform2D>(entity)) {
        //     return {0.0f, 0.0f};
        // }

        // Transform2D& transform = g_ecs.GetComponent<Transform2D>(entity);
        
        // // Get viewport center (handles split-screen, minimaps, etc.)
        // glm::vec2 viewport_center = GetViewportCenter();
        
        // // Calculate position relative to m_camera and apply zoom
        // glm::vec2 relative_position = transform.m_world_position - camera_transform.m_world_position;
        // glm::vec2 zoomed_position = relative_position * m_camera_zoom;

        // // Offset so m_camera is at viewport center
        // glm::vec2 screen_position = zoomed_position + viewport_center;

        // return screen_position;
        return glm::vec2(0.0f, 0.0f);
    }

    bool EditorCamera::IsCulled(EntityID entity) {
        // Texture& texture = g_ecs.GetComponent<Texture>(entity);
        
        // glm::vec2 screen_position = CalculateScreenPosition(entity);

        // // Get m_camera zoom and apply to texture size for culling check
        // glm::vec2 scaled_size = texture.m_size * m_camera_zoom;
        
        // float viewport_right = m_camera.x + m_camera.w;
        // float viewport_bottom = m_camera.y + m_camera.h;
        
        // // Cull if outside viewport bounds
        // return screen_position.x + scaled_size.x <= m_camera.x ||
        //     screen_position.y + scaled_size.y <= m_camera.y ||
        //     screen_position.x >= viewport_right ||
        //     screen_position.y >= viewport_bottom;
        return false;
    }
}