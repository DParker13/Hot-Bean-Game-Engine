#pragma once

#include <HotBeanEngine/defaults/systems/input/input_system.hpp>
#include <HotBeanEngine/defaults/systems/rendering/camera_system.hpp>

using namespace HBE::Default::Components;
using namespace HBE::Application;
using namespace HBE::Core;

namespace HBE::Default::Systems {
    class RenderSystem : public System {
        private:
            InputSystem& m_input_system;
            CameraSystem& m_camera_system;
            std::map<int, SDL_Texture*> m_layers;
            glm::ivec2 m_renderer_size = {0.0f, 0.0f};
        
        public:
            DEFINE_SIGNATURE(RenderSystem, Transform2D, Texture);
            RenderSystem(InputSystem& input_system, CameraSystem& camera_system)
                : System("Render System"), m_input_system(input_system), m_camera_system(camera_system) {};
            ~RenderSystem();

            void OnEntityAdded(Entity entity) override;
            void OnWindowResize(SDL_Event& event) override;
            void OnStart() override;
            void OnRender() override;
            void OnPostRender() override;

        private:
            void CreateTextureLayers();
            void CreateTextureLayerForEntity(Entity entity);
            void UpdateRendererSize();
            void RenderTextureToLayer(Entity entity);
            void RenderAllLayers();
            bool IsCulled(glm::vec2& screen_position, Texture& texture);
            bool IsCulled(Entity entity);
            glm::vec2 CalculateFinalPosition(Transform2D& transform, Texture& texture);
            void DrawDebugRect(const Texture& texture, const Transform2D& transform, const SDL_FRect* rect);
    };
}