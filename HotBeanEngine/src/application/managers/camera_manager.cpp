#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/application/managers/camera_manager.hpp>

namespace HBE::Application::Managers {
    float CameraManager::GetZoom(const Camera &camera) { return camera.m_zoom; }

    SDL_FRect CameraManager::GetViewport(const Camera &camera) {
        int screen_width, screen_height;
        SDL_GetRenderOutputSize(g_app.GetRenderer(), &screen_width, &screen_height);

        if (g_app.GetLoopManager().IsState(ApplicationState::Playing)) {
            return SDL_FRect{camera.m_viewport_position.x * screen_width, camera.m_viewport_position.y * screen_height,
                             camera.m_viewport_size.x * screen_width, camera.m_viewport_size.y * screen_height};
        }
        else {
            // In editor, ignore viewport and return full screen
            return SDL_FRect{0.0f, 0.0f, static_cast<float>(screen_width), static_cast<float>(screen_height)};
        }
    }

    glm::vec2 CameraManager::GetViewportCenter(const Camera &camera) {
        SDL_FRect viewport = GetViewport(camera);
        return glm::vec2(viewport.x + viewport.w * 0.5f, viewport.y + viewport.h * 0.5f);
    }

    std::vector<EntityID> CameraManager::GetAllActiveCameras() {
        std::vector<EntityID> active_cameras;

        for (EntityID entity : g_ecs.GetEntitiesWithComponents<Camera>()) {
            const auto &camera = g_ecs.GetComponent<Camera>(entity);

            if (camera.m_active) {
                active_cameras.push_back(entity);
            }
        }

        return active_cameras;
    }

    glm::vec2 CameraManager::CalculateScreenPosition(const Camera &camera, const Transform2D &camera_transform,
                                                     const Transform2D &entity_transform) {
        glm::vec2 viewport_center = GetViewportCenter(camera);
        glm::vec2 relative_position = entity_transform.m_world_position - camera_transform.m_world_position;
        glm::vec2 zoomed_position = relative_position * camera.m_zoom;
        glm::vec2 screen_position = zoomed_position + viewport_center;

        return screen_position;
    }

    bool CameraManager::IsCulled(const Camera &camera, const Transform2D &camera_transform,
                                 const Transform2D &entity_transform, const Texture &texture) {
        glm::vec2 screen_position = CalculateScreenPosition(camera, camera_transform, entity_transform);
        float zoom = GetZoom(camera);
        glm::vec2 scaled_size = texture.m_size * zoom;
        SDL_FRect viewport = GetViewport(camera);

        float viewport_right = viewport.x + viewport.w;
        float viewport_bottom = viewport.y + viewport.h;

        return screen_position.x + scaled_size.x <= viewport.x || screen_position.y + scaled_size.y <= viewport.y ||
               screen_position.x >= viewport_right || screen_position.y >= viewport_bottom;
    }
} // namespace HBE::Application::Managers