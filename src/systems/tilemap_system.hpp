#pragma once

#include <SDL.h>

#include "../managers/core_manager.hpp"
#include "../components/transform.hpp"
#include "../components/tile.hpp"

namespace Systems {
    class TileMapSystem : public System {
        public:
            TileMapSystem() = default;
            TileMapSystem(Core::CoreManager& coreManager, Uint32 x, Uint32 y);

            void CreateRect(SDL_Surface* surface, SDL_Renderer* renderer, SDL_Color* color, Components::Transform* transform);
            void RenderMap(SDL_Surface* surface, SDL_Renderer* renderer, Core::CoreManager& coreManager);

            std::string ToString() const;

        private:
            Uint32 _X;
            Uint32 _Y;
            
    };
}