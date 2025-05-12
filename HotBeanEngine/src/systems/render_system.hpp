#pragma once

#include <map>

#include "../core/core.hpp"

using namespace Components;
using namespace Core::Application;
using namespace Core::ECS;

namespace Systems {
    class RenderSystem : public System {
        public:
            std::map<int, SDL_Texture*> _layers;

            RenderSystem();
            ~RenderSystem();
            void OnEvent(SDL_Event& event) override;
            void OnRender() override;
            void OnPostRender() override;
    };
}