#pragma once

#include <map>

#include "../core/managers/core_manager.hpp"
#include "../components/transform-2d.hpp"
#include "../components/texture.hpp"

namespace Systems {
    class RenderSystem : public System {
        public:
            std::map<int, SDL_Texture*> _layers;

            RenderSystem(Core::CoreManager& coreManager);
            ~RenderSystem();
            void OnRender(SDL_Renderer* renderer, SDL_Window* window, SDL_Surface* surface) override;
            void OnPostRender(SDL_Renderer* renderer) override;
            std::string ToString() const;
    };
}