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

using namespace Components;

namespace Systems {
    RenderSystem::RenderSystem(App& app)
        : System(app) {
        app.SetupSystem<RenderSystem, Transform2D, Texture>(this);
    }

    RenderSystem::~RenderSystem() {
        // Clean up each texture layer
        for (const auto& layer : _layers) {
            SDL_DestroyTexture(layer.second);
        }
    }

    /**
     * @brief Handles an SDL event, resizing the renderer if the window is resized.
     * 
     * @param event 
     */
    void RenderSystem::OnEvent(SDL_Event& event) {
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
            _app.Log(LoggingType::INFO, "Window being resized - Resetting renderer...");

            SDL_Renderer* renderer = _app.GetRenderer();
            SDL_Window* window = SDL_GetWindowFromID(event.window.windowID);

            // Destroy the old surface and renderer
            SDL_DestroyWindowSurface(window);
            SDL_DestroyRenderer(renderer);

            // Create a new renderer
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == nullptr) {
                _app.Log(LoggingType::ERROR, std::string("Failed to create renderer: ") + SDL_GetError());
            }

            // Set the new renderer and window
            _app.SetRenderer(SDL_GetRenderer(window));
            _app.SetWindow(window);
            
            // Prepare the renderer for the next frame
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

            _app.Log(LoggingType::INFO, "Window finished resizing");
        }
    }
    
    void RenderSystem::OnRender() {
        auto* renderer = _app.GetRenderer();

        for (auto& entity : _entities) {
            auto& transform = _app.GetECSManager()->GetComponent<Transform2D>(entity);
            auto& texture = _app.GetECSManager()->GetComponent<Texture>(entity);

            // Create a new texture layer if it doesn't exist
            if (_layers.find(transform._layer) == _layers.end()) {
                // Get renderer size
                glm::ivec2 renderer_size = { 0, 0 };
                SDL_GetRendererOutputSize(renderer, &renderer_size.x, &renderer_size.y);

                // Create texture the size of the renderer
                _layers[transform._layer] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                            SDL_TEXTUREACCESS_TARGET, renderer_size.x, renderer_size.y);

                // Set blend mode to allow for transparency between layers
                SDL_SetTextureBlendMode(_layers[transform._layer], SDL_BLENDMODE_BLEND);
            }

            // Render entity texture to its appropriate layer texture
            for (int i = 0; i < _layers.size(); i++) {
                // Set render target to layer
                SDL_SetRenderTarget(renderer, _layers[transform._layer]);

                // Create rect the size of the texture
                const SDL_Rect* rect = new SDL_Rect({(int)transform._position.x, (int)transform._position.y,
                                                    texture._size.x, texture._size.y});

                // Render texture to layer
                SDL_RenderCopy(renderer, texture._texture, NULL, rect);

                // Free rect
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
    void RenderSystem::OnPostRender() {
        auto* renderer = _app.GetRenderer();

        for (auto& layer : _layers) {
            SDL_SetRenderTarget(renderer, layer.second);
            SDL_RenderClear(renderer);
        }
    }

    std::string RenderSystem::ToString() const {
        return "  Render System Entities: " + std::to_string(_entities.size()) + "\n";
    }
}