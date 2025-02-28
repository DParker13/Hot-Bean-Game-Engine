#include "tilemap_system.hpp"

namespace Systems {
    TileMapSystem::TileMapSystem(Core::CoreManager& coreManager)
        : System(coreManager) {
        coreManager.RegisterSystem<TileMapSystem>(this);

        coreManager.SetSignature<TileMapSystem, Components::Transform2D>();
        coreManager.SetSignature<TileMapSystem, Components::Tile>();
    }

    /**
     * @brief Initializes the tile map by calling InitMap with the given parameters.
     *
     * @details This function is a part of the System interface and is called by the
     *          CoreManager when the system is first initialized.
     */
    void TileMapSystem::OnInit() {
        InitMap(_coreManager, 10, 20, 50, 50);
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
    void TileMapSystem::OnRender(SDL_Renderer* renderer, SDL_Window* window, SDL_Surface* surface) {
        SDL_Color color = { 0xFF, 0xFF, 0xFF, 0xFF };

        for(auto& entity : _entities) {
            auto& transform = _coreManager.GetComponent<Components::Transform2D>(entity);
            auto& tile = _coreManager.GetComponent<Components::Tile>(entity);

            //CreateRect(surface, renderer, &color, &transform);
            CreateRect(renderer, &transform, &tile);
        }
    }

    void TileMapSystem::CreateRect(SDL_Renderer* renderer, Components::Transform2D* transform, Components::Tile* tile) {
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
    void TileMapSystem::InitMap(Core::CoreManager& coreManager, Uint8 tileSize, Uint8 spacing, Uint32 numTilesX, Uint32 numTilesY) {
        for (int x = 0; x < numTilesX; x++) {
            for (int y = 0; y < numTilesY; y++) {
                auto tile = GameObjects::Tile(&coreManager);
                tile.GetTile()._size = tileSize;
                tile.GetTile()._color = { static_cast<Uint8>(255 / ((x + 1) + (y + 1))),
                                        static_cast<Uint8>(255 / ((x + 1) + (y + 1))),
                                        static_cast<Uint8>(255 / ((x + 1) + (y + 1))), 0xFF };
                tile.GetTransform2D()._position.x = x * spacing;
                tile.GetTransform2D()._position.y = y * spacing;
            }
        }
    }
}