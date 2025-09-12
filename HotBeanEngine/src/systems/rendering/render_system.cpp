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

using namespace HBE::Components;

namespace Systems {
    RenderSystem::~RenderSystem() {
        // Clean up each texture layer
        for (const auto& layer : m_layers) {
            SDL_DestroyTexture(layer.second);
        }
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
        // Destroy all texture layers to be recreated with the new renderer size
        for (const auto& layer : m_layers) {
            SDL_DestroyTexture(layer.second);
        }
        m_layers.clear();

        g_app.SetupRendererAndWindow();

        // Create texture layers with the new renderer size
        CreateTextureLayers();
    }

    void RenderSystem::OnStart() {
        UpdateRendererSize();
    }
    
    /**
     * @brief Render each entity to its respective texture layer and then combine them on the screen
     * 
     */
    void RenderSystem::OnRender() {
        for (auto& entity : m_entities) {
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
        auto* renderer = g_app.GetRenderer();

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
            if (CullOutsideScreenSpace(entity)) {
                continue;
            }

            CreateTextureLayerForEntity(entity);
        }
    }

    void RenderSystem::CreateTextureLayerForEntity(Entity entity) {
        auto& transform = g_ecs.GetComponent<Transform2D>(entity);

        // Skips layers that have already been created
        if (m_layers.find(transform.m_layer) != m_layers.end()) {
            return;
        }

        auto* renderer = g_app.GetRenderer();
        SDL_Texture* current_layer = m_layers[transform.m_layer];

        // Create texture the size of the renderer (screen)
        current_layer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                    SDL_TEXTUREACCESS_TARGET, m_renderer_size.x, m_renderer_size.y);

        // Set blend mode to allow for transparency between layers
        SDL_SetTextureBlendMode(current_layer, SDL_BLENDMODE_BLEND);
    }

    void RenderSystem::UpdateRendererSize() {
        SDL_GetRendererOutputSize(g_app.GetRenderer(), &m_renderer_size.x, &m_renderer_size.y);
    }

    /**
     * @brief Render entity texture to its appropriate layer texture
     * 
     * @param entity Entity to render to layer
     */
    void RenderSystem::RenderEntityToLayer(Entity entity) {
        auto* renderer = g_app.GetRenderer();
        auto& transform = g_ecs.GetComponent<Transform2D>(entity);
        auto& texture = g_ecs.GetComponent<Texture>(entity);

        assert(m_layers.find(transform.m_layer) != m_layers.end() && "Layer does not exist");

        // Don't render anything off the screen
        if (CullOutsideScreenSpace(entity)) {
            return;
        }

        // Switch rendering target to current entity layer
        SDL_SetRenderTarget(renderer, m_layers[transform.m_layer]);

        // Create rect the size and position of the texture
        const SDL_Rect* rect = new SDL_Rect({(int)transform.m_screen_position.x, (int)transform.m_screen_position.y,
                                            texture.m_size.x, texture.m_size.y});

        // Render texture to layer
        SDL_RenderCopy(renderer, texture.m_texture, NULL, rect);

        // If Debug key (F1) is pressed, draw a red outline around the entity
        if (m_input_system.m_keys_pressed.find(InputSystem::DEBUG_KEY) != m_input_system.m_keys_pressed.end()) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderDrawRect(renderer, rect);
        }

        // Free rect
        if(rect) {
            delete rect;
        }
    }

    /**
     * @brief Renders all layers to the screen in order
     */
    void RenderSystem::RenderAllLayers() {
        auto* renderer = g_app.GetRenderer();

        // Render each layer
        for (auto& layer : m_layers) {
            SDL_SetRenderTarget(renderer, NULL);
            SDL_RenderCopy(renderer, layer.second, NULL, NULL);
        }
    }

    bool RenderSystem::CullOutsideScreenSpace(Entity entity) {
        auto& transform = g_ecs.GetComponent<Transform2D>(entity);
        auto& texture = g_ecs.GetComponent<Texture>(entity);

        return transform.m_screen_position.x + texture.m_size.x <= 0 ||
            transform.m_screen_position.y + texture.m_size.y <= 0 ||
            transform.m_screen_position.x >= m_renderer_size.x ||
            transform.m_screen_position.y >= m_renderer_size.y;
    }
}