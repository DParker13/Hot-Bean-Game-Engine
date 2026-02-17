#pragma once

#include <HotBeanEngine/defaults/components/miscellaneous/camera.hpp>
#include <HotBeanEngine/defaults/components/miscellaneous/transform_2d.hpp>
#include <HotBeanEngine/defaults/components/rendering/texture.hpp>

namespace HBE::Application::Managers {
    using namespace HBE::Core;
    using namespace HBE::Default::Components;

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
        float GetZoom(const HBE::Default::Components::Camera &camera);
        SDL_FRect GetViewport(const HBE::Default::Components::Camera &camera);
        glm::vec2 GetViewportCenter(const HBE::Default::Components::Camera &camera);
        glm::vec2 CalculateScreenPosition(const HBE::Default::Components::Camera &camera,
                                          const HBE::Default::Components::Transform2D &camera_transform,
                                          const HBE::Default::Components::Transform2D &entity_transform);
        bool IsCulled(const HBE::Default::Components::Camera &camera,
                      const HBE::Default::Components::Transform2D &camera_transform,
                      const HBE::Default::Components::Transform2D &entity_transform,
                      const HBE::Default::Components::Texture &texture);
    };
} // namespace HBE::Application::Managers