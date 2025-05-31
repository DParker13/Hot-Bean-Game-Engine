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
        InitMap(10, 15, 16, 16);
    }

    void TileMapSystem::CreateRect(Transform2D* transform, Components::Tile* tile, Texture* texture) {
        auto* renderer = App::GetInstance().GetRenderer();

        tile->m_vertices[0] = { transform->m_screen_position.x, transform->m_screen_position.y, tile->m_color };
        tile->m_vertices[1] = { transform->m_screen_position.x, transform->m_screen_position.y + tile->m_size, tile->m_color };
        tile->m_vertices[2] = { transform->m_screen_position.x + tile->m_size, transform->m_screen_position.y, tile->m_color };
        tile->m_vertices[3] = { transform->m_screen_position.x + tile->m_size, transform->m_screen_position.y + tile->m_size, tile->m_color };
        
        // Render the vertex buffer
        if (!texture) {
            App::GetInstance().Log(LoggingType::FATAL, "Texture doesn't exist");
        }
        
        SDL_RenderGeometry(renderer, NULL, tile->m_vertices,
                            sizeof(tile->m_vertices) / sizeof(tile->m_vertices[0]), tile->m_INDICES,
                            sizeof(tile->m_INDICES) / sizeof(tile->m_INDICES[0]));
    }

    void TileMapSystem::InitMap(Uint8 tileSize, Uint8 spacing, Uint32 numTilesX, Uint32 numTilesY) {
        App& app = App::GetInstance();

        auto mapEntity = app.CreateEntity();
        app.AddComponent<Texture>(mapEntity, Texture());
        app.AddComponent<Transform2D>(mapEntity, Transform2D());
        auto& texture = app.GetECSManager()->GetComponent<Texture>(mapEntity);
        app.GetECSManager()->GetComponent<Texture>(mapEntity)._size = { numTilesX * tileSize, numTilesY * tileSize };
        
        for (int x = 0; x < numTilesX; x++) {
            for (int y = 0; y < numTilesY; y++) {
                auto tile = GameObjects::Tile();
                tile.GetComponent<Tile>().m_size = tileSize;
                tile.GetComponent<Tile>().m_color = { static_cast<Uint8>(255 / (x + 1)),
                                        static_cast<Uint8>(255 / (y + 1)),
                                        static_cast<Uint8>(255 / ((x + 1) + (y + 1))), 0xFF };
                tile.GetComponent<Transform2D>().m_world_position.x = x * spacing;
                tile.GetComponent<Transform2D>().m_world_position.y = y * spacing;
                tile.GetComponent<Transform2D>().m_layer = 10;

                CreateRect(&tile.GetComponent<Transform2D>(), &tile.GetComponent<Tile>(), &texture);
            }
        }

        
    }
}