#pragma once

#include <HotBeanEngine/defaults/components/miscellaneous/camera.hpp>
#include <HotBeanEngine/defaults/components/miscellaneous/transform_2d.hpp>
#include <HotBeanEngine/defaults/components/rendering/texture.hpp>

namespace HBE::Application::Managers {
    using HBE::Default::Components::Camera;
    using HBE::Default::Components::Texture;
    using HBE::Default::Components::Transform2D;

    /**
     * @class CameraManager
     * @brief Manages cameras within the application.
     *
     * The CameraManager is responsible for handling the creation, retrieval,
     * and management of cameras used in the rendering process.
     */
    class CameraManager {
    private:
        std::unordered_map<int, SDL_Texture *> m_layers; ///< Map of layer IDs to SDL_Textures

    public:
        CameraManager() = default;
        ~CameraManager() = default;

        std::vector<EntityID> GetAllActiveCameras();
        float GetZoom(const Camera &camera);
        SDL_FRect GetViewport(const Camera &camera);
        glm::vec2 GetViewportCenter(const Camera &camera);
        glm::vec2 CalculateScreenPosition(const Camera &camera, const Transform2D &camera_transform,
                                          const Transform2D &entity_transform);
        bool IsCulled(const Camera &camera, const Transform2D &camera_transform, const Transform2D &entity_transform,
                      const Texture &texture);
    };
} // namespace HBE::Application::Managers