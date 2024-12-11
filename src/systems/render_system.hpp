#pragma once

#include <SDL.h>
#include <memory>
#include <iostream>

#include "../core/ecs.hpp"
#include "../core/core_manager.hpp"
#include "../components/transform.hpp"

namespace Systems {
    class RenderSystem : public System {
        public:
            void Render(SDL_Surface* surface, SDL_Renderer* renderer, Core::CoreManager& coreManager);
            void CreateRect(SDL_Surface* surface, SDL_Renderer* renderer, SDL_Color* color, Components::Transform* transform);
            void Print() const;
    };
}