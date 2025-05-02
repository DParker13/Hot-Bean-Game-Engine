#include "tilemap_system.hpp"

namespace Systems {
    TileMapSystem::TileMapSystem() : System() {
        App::GetInstance().SetupSystem<TileMapSystem, Transform2D, Tile, RigidBody>(this);
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
     * @brief Renders all entities in the system to the screen.
     *
     * @details This function is a part of the System interface and is called by the
     *          CoreManager when the system is updated.
     *
     * @param[in] renderer The SDL_Renderer to render to.
     * @param[in] window The SDL_Window the renderer is rendering to.
     * @param[in] surface The SDL_Surface of the window.
     */
    void TileMapSystem::OnRender() {
        App& app = App::GetInstance();
        SDL_Color color = { 0xFF, 0xFF, 0xFF, 0xFF };

        for(auto& entity : _entities) {
            auto& transform = app.GetECSManager()->GetComponent<Transform2D>(entity);
            auto& tile = app.GetECSManager()->GetComponent<Tile>(entity);

            CreateRect(&transform, &tile);
        }
    }

    void TileMapSystem::CreateRect(Transform2D* transform, Components::Tile* tile) {
        auto* renderer = App::GetInstance().GetRenderer();

        tile->_vertices[0] = { transform->_position.x, transform->_position.y, tile->_color };
        tile->_vertices[1] = { transform->_position.x, transform->_position.y + tile->_size, tile->_color };
        tile->_vertices[2] = { transform->_position.x + tile->_size, transform->_position.y, tile->_color };
        tile->_vertices[3] = { transform->_position.x + tile->_size, transform->_position.y + tile->_size, tile->_color };
        
        // Render the vertex buffer
        SDL_RenderGeometry(renderer, NULL, tile->_vertices,
                            sizeof(tile->_vertices) / sizeof(tile->_vertices[0]), tile->_INDICES,
                            sizeof(tile->_INDICES) / sizeof(tile->_INDICES[0]));
    }

    std::string TileMapSystem::ToString() const {
        return "";
    }

    // Should this be defined in TileMapSystem instead?
    void TileMapSystem::InitMap(Uint8 tileSize, Uint8 spacing, Uint32 numTilesX, Uint32 numTilesY) {
        App& app = App::GetInstance();
        
        for (int x = 0; x < numTilesX; x++) {
            for (int y = 0; y < numTilesY; y++) {
                auto tile = GameObjects::Tile();
                tile.GetComponent<Tile>()._size = tileSize;
                tile.GetComponent<Tile>()._color = { static_cast<Uint8>(255 / ((x + 1) + (y + 1))),
                                        static_cast<Uint8>(255 / ((x + 1) + (y + 1))),
                                        static_cast<Uint8>(255 / ((x + 1) + (y + 1))), 0xFF };
                tile.GetComponent<Transform2D>()._position.x = x * spacing;
                tile.GetComponent<Transform2D>()._position.y = y * spacing;
            }
        }
    }
}