#include "tilemap_system.hpp"

namespace Systems {
    TileMapSystem::TileMapSystem(Core::CoreManager& coreManager)
        : System(coreManager) {
        coreManager.RegisterSystem<TileMapSystem>(this);

        coreManager.SetSignature<TileMapSystem, Components::Transform>();
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
            auto& transform = _coreManager.GetComponent<Components::Transform>(entity);
            auto& tile = _coreManager.GetComponent<Components::Tile>(entity);

            //CreateRect(surface, renderer, &color, &transform);
            CreateRect(renderer, &transform, &tile);
        }

        // Renders all rectangles to the screen
        // if (!_rects.empty()) {
        //     SDL_RenderFillRectsF(renderer, _rects.data(), _rects.size());
        //     _rects.clear();
        // }
    }

    // Function to fill a rectangle on an SDL_Surface
    void TileMapSystem::CreateRect(SDL_Surface* surface, SDL_Renderer* renderer,
                                SDL_Color* color, Components::Transform* transform) {
        SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);

        // Define a rectangle and insert it into the vector
        _rects.emplace_back() = { transform->position.x, transform->position.y, 10, 10 };
    }

    void TileMapSystem::CreateRect(SDL_Renderer* renderer, Components::Transform* transform, Components::Tile* tile) {
        tile->_vertices[0] = { transform->position.x, transform->position.y, tile->_color };
        tile->_vertices[1] = { transform->position.x, transform->position.y + tile->_size, tile->_color };
        tile->_vertices[2] = { transform->position.x + tile->_size, transform->position.y, tile->_color };
        tile->_vertices[3] = { transform->position.x + tile->_size, transform->position.y + tile->_size, tile->_color };
        
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
                tile.GetTransform().position.x = x * spacing;
                tile.GetTransform().position.y = y * spacing;
            }
        }
    }
}