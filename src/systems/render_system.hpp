#pragma once

#include <SDL.h>

#include "../managers/core_manager.hpp"
#include "../components/transform.hpp"
#include "../components/texture.hpp"

namespace Systems {
    class RenderSystem : public System {
        public:
            RenderSystem(Core::CoreManager& coreManager);
            void Render(SDL_Surface* surface, SDL_Renderer* renderer, Core::CoreManager& coreManager);
            std::string ToString() const;
    };
}