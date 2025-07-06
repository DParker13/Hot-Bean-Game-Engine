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
        InitMap(10, 15, 40, 40);
    }

    void TileMapSystem::CreateRect(Entity entity) {
        Transform2D& transform = App::GetInstance().GetComponent<Transform2D>(entity);
        Tile& tile = App::GetInstance().GetComponent<Core::Components::Tile>(entity);
        auto* renderer = App::GetInstance().GetRenderer();

        tile.m_vertices[0] = { transform.m_world_position.x, transform.m_world_position.y, tile.m_color };
        tile.m_vertices[1] = { transform.m_world_position.x, transform.m_world_position.y + tile.m_size, tile.m_color };
        tile.m_vertices[2] = { transform.m_world_position.x + tile.m_size, transform.m_world_position.y, tile.m_color };
        tile.m_vertices[3] = { transform.m_world_position.x + tile.m_size, transform.m_world_position.y + tile.m_size, tile.m_color };
    }

    void TileMapSystem::InitMap(Uint8 tile_size, Uint8 spacing, Uint32 num_tiles_x, Uint32 num_tiles_y) {
        App& app = App::GetInstance();

        // Setup tilemap texture entity
        Entity map_entity = app.CreateEntity();
        app.AddComponent<Texture>(map_entity);
        app.AddComponent<Transform2D>(map_entity);
        map_texture = &app.GetECSManager()->GetComponent<Texture>(map_entity);
        map_texture->m_size = { num_tiles_x * tile_size, num_tiles_y * tile_size };
        
        for (int x = 0; x < num_tiles_x; x++) {
            for (int y = 0; y < num_tiles_y; y++) {
                auto tile = GameObjects::Tile();
                tile.GetComponent<Tile>().m_size = tile_size;
                tile.GetComponent<Tile>().m_color = { static_cast<Uint8>(255 / (x + 1)),
                                        static_cast<Uint8>(255 / (y + 1)),
                                        static_cast<Uint8>(255 / ((x + 1) + (y + 1))), 0xFF };
                tile.GetComponent<Transform2D>().m_world_position.x = x * spacing;
                tile.GetComponent<Transform2D>().m_world_position.y = y * spacing;
                CreateRect(tile.GetEntity());
            }
        }
    }

    void TileMapSystem::OnRender() {
        auto* renderer = App::GetInstance().GetRenderer();

        for (auto& entity : m_entities) {
            Tile& tile = App::GetInstance().GetComponent<Core::Components::Tile>(entity);
            
            // Render the vertex buffer
            if (!map_texture) {
                LOG(LoggingType::FATAL, "Texture doesn't exist");
            }
            SDL_SetRenderTarget(renderer, map_texture->m_texture);
            SDL_RenderGeometry(renderer, NULL, tile.m_vertices,
                            sizeof(tile.m_vertices), tile.m_INDICES, sizeof(tile.m_INDICES));
            SDL_SetRenderTarget(renderer, NULL);
        }
    }
}