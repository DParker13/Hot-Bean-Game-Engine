#pragma once

#include <map>
#include <core.hpp>

#include "../components/transform_2d.hpp"
#include "../components/texture.hpp"

using namespace Components;
using namespace Core::Application;
using namespace Core::ECS;

namespace Systems {
    class RenderSystem : public System {
        public:
            std::map<int, SDL_Texture*> _layers;

            RenderSystem(App& app);
            ~RenderSystem();
            void OnEvent(SDL_Event& event) override;
            void OnRender() override;
            void OnPostRender() override;
            std::string ToString() const;
    };
}