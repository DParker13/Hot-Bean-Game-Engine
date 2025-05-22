#pragma once

#include <HotBeanEngine.hpp>

using namespace Components;
using namespace Core::Application;
using namespace Core::ECS;

namespace Systems {
    class TileMapSystem : public System {
        public:
            TileMapSystem() = default;

            //System Interface Overrides
            void SetSignature() override;
            void OnStart() override;
            void OnRender() override;

            void CreateRect(SDL_Color* color, Transform2D* transform);
            void CreateRect(Transform2D* transform, Components::Tile* tile);
            void InitMap(Uint8 tileSize, Uint8 spacing, Uint32 numTilesX, Uint32 numTilesY);

        private:
            std::vector<SDL_FRect> _rects;
            
    };
}