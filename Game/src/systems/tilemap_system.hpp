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

            void CreateRect(Transform2D* transform, Components::Tile* tile, Texture* texture);
            void InitMap(Uint8 tileSize, Uint8 spacing, Uint32 numTilesX, Uint32 numTilesY);

        private:
            std::vector<SDL_FRect> m_rects;
            
    };
}