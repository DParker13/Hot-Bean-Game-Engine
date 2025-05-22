#include "tilemap_system.hpp"

namespace Systems {
    void TileMapSystem::SetSignature() {
        SETUP_SYSTEM(TileMapSystem, Transform2D, Tile);
    }

    /**
     * @brief Initializes the tile map by calling InitMap with the given parameters.
     *
     * @details This function is a part of the System interface and is called by the
     *          CoreManager when the system is first initialized.
     */
    void TileMapSystem::OnStart() {
        InitMap(10, 15, 50, 50);
    }

    /**
     * @brief Renders the tile map by calling CreateRect for each tile in the tile map.
     */
    void TileMapSystem::OnRender() {
        App& app = App::GetInstance();

        for(auto& entity : m_entities) {
            auto& transform = app.GetECSManager()->GetComponent<Transform2D>(entity);
            auto& tile = app.GetECSManager()->GetComponent<Tile>(entity);

            CreateRect(&transform, &tile);
        }
    }

    void TileMapSystem::CreateRect(Transform2D* transform, Components::Tile* tile) {
        auto* renderer = App::GetInstance().GetRenderer();

        tile->m_vertices[0] = { transform->m_screen_position.x, transform->m_screen_position.y, tile->m_color };
        tile->m_vertices[1] = { transform->m_screen_position.x, transform->m_screen_position.y + tile->m_size, tile->m_color };
        tile->m_vertices[2] = { transform->m_screen_position.x + tile->m_size, transform->m_screen_position.y, tile->m_color };
        tile->m_vertices[3] = { transform->m_screen_position.x + tile->m_size, transform->m_screen_position.y + tile->m_size, tile->m_color };
        
        // Render the vertex buffer
        SDL_RenderGeometry(renderer, NULL, tile->m_vertices,
                            sizeof(tile->m_vertices) / sizeof(tile->m_vertices[0]), tile->m_INDICES,
                            sizeof(tile->m_INDICES) / sizeof(tile->m_INDICES[0]));
    }

    void TileMapSystem::InitMap(Uint8 tileSize, Uint8 spacing, Uint32 numTilesX, Uint32 numTilesY) {
        App& app = App::GetInstance();
        
        for (int x = 0; x < numTilesX; x++) {
            for (int y = 0; y < numTilesY; y++) {
                auto tile = GameObjects::Tile();
                tile.GetComponent<Tile>().m_size = tileSize;
                tile.GetComponent<Tile>().m_color = { static_cast<Uint8>(255 / ((x + 1) + (y + 1))),
                                        static_cast<Uint8>(255 / ((x + 1) + (y + 1))),
                                        static_cast<Uint8>(255 / ((x + 1) + (y + 1))), 0xFF };
                tile.GetComponent<Transform2D>().m_world_position.x = x * spacing;
                tile.GetComponent<Transform2D>().m_world_position.y = y * spacing;
                tile.GetComponent<Transform2D>().m_layer = 10;
            }
        }
    }
}