#pragma once

#include "../../application/all_application.hpp"

using namespace Core::Components;
using namespace Core::Application;
using namespace Core::ECS;

namespace Core::Systems {
    class RenderSystem : public System {
        public:
            std::map<int, SDL_Texture*> m_layers;

            RenderSystem() = default;
            ~RenderSystem();

            void SetSignature() override;
            void OnEntityAdded(Entity entity) override;
            void OnWindowResize(SDL_Event& event) override;
            void OnRender() override;
            void OnPostRender() override;

        private:
            void CreateTextureLayers();
            void CreateTextureLayerForEntity(Entity entity);
            glm::ivec2 GetRendererSize();
            void RenderEntityToLayer(Entity entity);
            void RenderAllLayers();
    };
}