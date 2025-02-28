/**
 * @file render_system.cpp
 * @author Daniel Parker
 * @brief Rendering system implementation.
 * Responsible for rendering game entities to the screen using SDL.
 * @version 0.1
 * @date 2025-02-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "render_system.hpp"

namespace Systems {
    RenderSystem::RenderSystem(Core::CoreManager& coreManager)
        : System(coreManager) {
        coreManager.RegisterSystem<RenderSystem>(this);

        coreManager.SetSignature<RenderSystem, Components::Transform2D>();
        coreManager.SetSignature<RenderSystem, Components::Texture>();
    }

    RenderSystem::~RenderSystem() {
        for (const auto& layer : _layers) {
            SDL_DestroyTexture(layer.second);
        }
    }
    
    void RenderSystem::OnRender(SDL_Renderer* renderer, SDL_Window* window, SDL_Surface* surface) {
        for (auto& entity : _entities) {
            auto& transform = _coreManager.GetComponent<Components::Transform2D>(entity);
            auto& texture = _coreManager.GetComponent<Components::Texture>(entity);

            // Create a new texture layer if it doesn't exist
            if (_layers.find(transform._layer) == _layers.end()) {
                glm::ivec2 renderer_size = { 0, 0 };
                SDL_GetRendererOutputSize(renderer, &renderer_size.x, &renderer_size.y);
                _layers[transform._layer] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                            SDL_TEXTUREACCESS_TARGET, renderer_size.x, renderer_size.y);
                SDL_SetTextureBlendMode(_layers[transform._layer], SDL_BLENDMODE_BLEND);
            }

            // Render entity texture to its appropriate layer texture
            for (int i = 0; i < _layers.size(); i++) {
                SDL_SetRenderTarget(renderer, _layers[transform._layer]);

                const SDL_Rect* rect = new SDL_Rect({(int)transform._position.x, (int)transform._position.y,
                                                    texture._size.x, texture._size.y});
                SDL_RenderCopy(renderer, texture._texture, NULL, rect);

                if(rect) {
                    delete rect;
                }
            }
        }

        // Render all layers to screen in order
        for (int i = 0; i < _layers.size(); i++) {
            if (_layers[i] == nullptr) {
                continue;
            }

            SDL_SetRenderTarget(renderer, NULL);
            SDL_RenderCopy(renderer, _layers[i], NULL, NULL);
        }
    }

    /**
     * @brief Clears all the layer textures for the next frame.
     * 
     * @param renderer 
     */
    void RenderSystem::OnPostRender(SDL_Renderer* renderer) {
        for (auto& layer : _layers) {
            SDL_SetRenderTarget(renderer, layer.second);
            SDL_RenderClear(renderer);
        }
    }

    std::string RenderSystem::ToString() const {
        return "  Render System Entities: " + std::to_string(_entities.size()) + "\n";
    }
}