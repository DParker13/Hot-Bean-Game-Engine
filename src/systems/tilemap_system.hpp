#pragma once

#include <SDL.h>

#include "../core/managers/core_manager.hpp"
#include "../gameobjects/tile.hpp"

namespace Systems {
    class TileMapSystem : public System {
        public:
            TileMapSystem(Core::CoreManager& coreManager);

            //System Interface Overrides
            void OnInit() override;
            void OnRender(SDL_Renderer* renderer, SDL_Window* window, SDL_Surface* surface) override;

            void CreateRect(SDL_Surface* surface, SDL_Renderer* renderer, SDL_Color* color, Components::Transform2D* transform);
            void CreateRect(SDL_Renderer* renderer, Components::Transform2D* transform, Components::Tile* tile);
            void InitMap(Core::CoreManager& coreManager, Uint8 tileSize, Uint8 spacing, Uint32 numTilesX, Uint32 numTilesY);


            std::string ToString() const;

        private:
            std::vector<SDL_FRect> _rects;
            
    };
}