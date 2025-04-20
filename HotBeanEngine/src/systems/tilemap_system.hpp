#pragma once

#include "../core/core.hpp"
#include "../gameobjects/tile.hpp"

using namespace Components;
using namespace Core::Application;
using namespace Core::ECS;

namespace Systems {
    class TileMapSystem : public System {
        public:
            TileMapSystem();

            //System Interface Overrides
            void OnInit() override;
            void OnRender() override;

            void CreateRect(SDL_Color* color, Transform2D* transform);
            void CreateRect(Transform2D* transform, Components::Tile* tile);
            void InitMap(Uint8 tileSize, Uint8 spacing, Uint32 numTilesX, Uint32 numTilesY);


            std::string ToString() const;

        private:
            std::vector<SDL_FRect> _rects;
            
    };
}