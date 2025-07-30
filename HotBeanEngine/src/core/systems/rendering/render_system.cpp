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

using namespace Core::Components;

namespace Core::Systems {
    RenderSystem::~RenderSystem() {
        // Clean up each texture layer
        for (const auto& layer : m_layers) {
            SDL_DestroyTexture(layer.second);
        }
    }

    void RenderSystem::SetSignature() {
        SETUP_SYSTEM(RenderSystem, Transform2D, Texture);
    }

    void RenderSystem::OnEntityAdded(Entity entity) {
        CreateTextureLayerForEntity(entity);
    }

    /**
     * @brief Called when the window is resized
     * 
     * @param event The SDL window event
     */
    void RenderSystem::OnWindowResize(SDL_Event& event) {
        App& app = App::GetInstance();
        LOG(LoggingType::INFO, "Window being resized - Resetting renderer...");

        SDL_Renderer* renderer = app.GetRenderer();
        SDL_Window* window = SDL_GetWindowFromID(event.window.windowID);

        // Destroy the old surface and renderer
        SDL_DestroyWindowSurface(window);
        SDL_DestroyRenderer(renderer);

        // Create a new renderer
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == nullptr) {
            LOG(LoggingType::ERROR, std::string("Failed to create renderer: ") + SDL_GetError());
        }

        // Set the new renderer and window
        app.SetRenderer(SDL_GetRenderer(window));
        app.SetWindow(window);
        
        // Prepare the renderer for the next frame
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

        // Create texture layers with the new renderer size
        CreateTextureLayers();

        LOG(LoggingType::INFO, "Window finished resizing");
    }
    
    /**
     * @brief Render each entity to its respective texture layer and then combine them on the screen
     * 
     */
    void RenderSystem::OnRender() {
        for (auto& entity : m_entities) {
            auto& transform = App::GetInstance().GetECSManager()->GetComponent<Transform2D>(entity);

            // Render entity to its respective texture layer
            RenderEntityToLayer(entity);
        }

        // Render all layers in order (layer 0 first, layer 1 second, etc...)
        RenderAllLayers();
    }

    /**
     * @brief Clears all the layer textures for the next frame.
     */
    void RenderSystem::OnPostRender() {
        auto* renderer = App::GetInstance().GetRenderer();

        // Clear all layers
        for (auto& layer : m_layers) {
            SDL_SetRenderTarget(renderer, layer.second);
            SDL_RenderClear(renderer);
        }
    }

    /**
     * @brief Creates all texture layers for each entity
     */
    void RenderSystem::CreateTextureLayers() {
        for (auto entity : m_entities) {
            CreateTextureLayerForEntity(entity);
        }
    }

    void RenderSystem::CreateTextureLayerForEntity(Entity entity) {
        auto& transform = App::GetInstance().GetECSManager()->GetComponent<Transform2D>(entity);

        // Skips layers that have already been created
        if (m_layers.find(transform.m_layer) != m_layers.end()) {
            return;
        }

        auto* renderer = App::GetInstance().GetRenderer();
        SDL_Texture* current_layer = m_layers[transform.m_layer];
        auto renderer_size = GetRendererSize();

        // Create texture the size of the renderer (screen)
        current_layer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                    SDL_TEXTUREACCESS_TARGET, renderer_size.x, renderer_size.y);

        // Set blend mode to allow for transparency between layers
        SDL_SetTextureBlendMode(current_layer, SDL_BLENDMODE_BLEND);
    }

    glm::ivec2 RenderSystem::GetRendererSize() {
        // Get renderer size
        glm::ivec2 renderer_size = { 0, 0 };
        SDL_GetRendererOutputSize(App::GetInstance().GetRenderer(), &renderer_size.x, &renderer_size.y);

        return renderer_size;
    }

    /**
     * @brief Render entity texture to its appropriate layer texture
     * 
     * @param entity Entity to render to layer
     */
    void RenderSystem::RenderEntityToLayer(Entity entity) {
        App& app = App::GetInstance();
        auto* renderer = app.GetRenderer();
        auto& transform = app.GetECSManager()->GetComponent<Transform2D>(entity);
        auto& texture = app.GetECSManager()->GetComponent<Texture>(entity);

        assert(m_layers.find(transform.m_layer) != m_layers.end() && "Layer does not exist");

        // Switch rendering target to current entity layer
        SDL_SetRenderTarget(renderer, m_layers[transform.m_layer]);

        // Create rect the size and position of the texture
        const SDL_Rect* rect = new SDL_Rect({(int)transform.m_screen_position.x, (int)transform.m_screen_position.y,
                                            texture.m_size.x, texture.m_size.y});

        // Render texture to layer
        SDL_RenderCopy(renderer, texture.m_texture, NULL, rect);

        // Free rect
        if(rect) {
            delete rect;
        }
    }

    /**
     * @brief Renders all layers to the screen in order
     */
    void RenderSystem::RenderAllLayers() {
        auto* renderer = App::GetInstance().GetRenderer();

        // Render each layer
        for (auto& layer : m_layers) {
            SDL_SetRenderTarget(renderer, NULL);
            SDL_RenderCopy(renderer, layer.second, NULL, NULL);
        }
    }
}