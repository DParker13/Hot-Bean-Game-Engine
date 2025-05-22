#pragma once

#include "../core/core.hpp"

using namespace Components;
using namespace Core::Application;
using namespace Core::ECS;

namespace Systems {
    class RenderSystem : public System {
        public:
            std::map<int, SDL_Texture*> m_layers;

            RenderSystem() = default;
            ~RenderSystem();

            void SetSignature() override;
            void OnWindowResize(SDL_Event& event) override;
            void OnRender() override;
            void OnPostRender() override;

        private:
            void CreateTextureLayer(Entity entity);
            void RenderEntityToLayer(Entity entity);
            void RenderAllLayers();
    };
}