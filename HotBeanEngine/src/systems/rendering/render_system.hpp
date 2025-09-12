#pragma once

#include "../input/input_system.hpp"

using namespace HBE::Components;
using namespace HBE::Application;
using namespace HBE::Core;

namespace Systems {
    class RenderSystem : public System {
        private:
            InputSystem& m_input_system;
            std::map<int, SDL_Texture*> m_layers;
            glm::ivec2 m_renderer_size;
        
        public:
            DEFINE_SIGNATURE(RenderSystem, Transform2D, Texture);
            RenderSystem(InputSystem& input_system) : m_input_system(input_system) {};
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
            void RenderEntityToLayer(Entity entity);
            void RenderAllLayers();
            bool CullOutsideScreenSpace(Entity entity);
    };
}