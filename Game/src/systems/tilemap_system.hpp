#pragma once

#include <HotBeanEngine.hpp>

using namespace HBE::Components;
using namespace HBE::Application;
using namespace HBE::Core;

namespace Systems {
    class TileMapSystem : public System {
        public:
            TileMapSystem() = default;

            //System Interface Overrides
            void SetSignature() override;
            void OnStart() override;
            void OnRender() override;

        private:
            std::vector<SDL_FRect> m_rects;
            Texture* map_texture;

            void CreateRect(Entity entity);
            void InitMap(Uint8 tileSize, Uint8 spacing, Uint32 numTilesX, Uint32 numTilesY);
            
    };
}