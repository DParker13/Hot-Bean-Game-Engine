/**
 * @file render_system.cpp
 * @author Daniel Parker
 * @brief System for rendering textures to their respective layers.
 * @version 0.1
 * @date 2025-02-18
 * 
 * @copyright Copyright (c) 2025
 */

#include <HotBeanEngine/defaults/systems/rendering/render_system.hpp>

namespace HBE::Default::Systems {
    RenderSystem::~RenderSystem() {
        // Clean up each texture layer
        for (const auto& layer : m_layers) {
            SDL_DestroyTexture(layer.second);
        }
    }

    void RenderSystem::OnEntityAdded(EntityID entity) {
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

        int new_w = event.window.data1;
        int new_h = event.window.data2;
        SDL_SetRenderLogicalPresentation(g_app.GetRenderer(), new_w, new_h, SDL_LOGICAL_PRESENTATION_DISABLED);
        SDL_SetRenderViewport(g_app.GetRenderer(), nullptr);

        UpdateRendererSize();

        // Create texture layers with the new renderer size
        CreateTextureLayers();
    }

    void RenderSystem::OnStart() {
        UpdateRendererSize();
    }
    
    /**
     * @brief Render each entity to its respective texture layer and then combine them on the screen
     */
    void RenderSystem::OnRender() {
        for (auto& entity : m_entities) {
            // Render entity to its respective texture layer
            RenderTextureToLayer(entity);
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
        for (auto& entity : m_entities) {
            if (IsCulled(entity)) {
                continue;
            }

            CreateTextureLayerForEntity(entity);
        }
    }

    /**
     * @brief Creates a texture layer for the entity's layer if it doesn't already exist
     * @param entity EntityID to create layer for
     */
    void RenderSystem::CreateTextureLayerForEntity(EntityID entity) {
        auto& transform = g_ecs.GetComponent<Transform2D>(entity);

        // Skips layers that have already been created
        if (m_layers.find(transform.m_layer) != m_layers.end()) {
            return;
        }

        SDL_Texture* current_layer = m_layers[transform.m_layer];

        // Create texture the size of the renderer (screen)
        current_layer = SDL_CreateTexture(g_app.GetRenderer(), SDL_PIXELFORMAT_RGBA8888,
                                    SDL_TEXTUREACCESS_TARGET, m_renderer_size.x, m_renderer_size.y);

        // Set blend mode to allow for transparency between layers
        SDL_SetTextureBlendMode(current_layer, SDL_BLENDMODE_BLEND);
    }

    void RenderSystem::UpdateRendererSize() {
        SDL_GetCurrentRenderOutputSize(g_app.GetRenderer(), &m_renderer_size.x, &m_renderer_size.y);
    }

    /**
     * @brief Render entity texture to its appropriate layer texture
     * @param entity EntityID to render to layer
     */
    void RenderSystem::RenderTextureToLayer(EntityID entity) {
        auto* renderer = g_app.GetRenderer();
        auto& transform = g_ecs.GetComponent<Transform2D>(entity);
        auto& texture = g_ecs.GetComponent<Texture>(entity);

        assert(m_layers.find(transform.m_layer) != m_layers.end() && "Layer does not exist");
        
        glm::vec2 screen_position = CalculateFinalPosition(transform, texture);

        // Don't render anything off the screen
        if (IsCulled(screen_position, texture)) {
            return;
        }

        // Switch rendering target to current entity layer
        SDL_SetRenderTarget(renderer, m_layers[transform.m_layer]);
        
        // Create rect the size and position of the texture
        const SDL_FRect* rect = new SDL_FRect({screen_position.x, screen_position.y,
                                            texture.m_size.x, texture.m_size.y});

        if (texture.m_texture == nullptr) {
            LOG(LoggingType::ERROR, "Entity " + std::to_string(entity) + " has no texture to render!");
            return;
        }

        // Render texture to layer
        SDL_RenderTextureRotated(renderer, texture.m_texture, NULL, rect,
            transform.m_world_rotation, NULL, SDL_FLIP_NONE);

        // TODO: Optimize debug rendering to not create/destroy texture and rect every frame?
        // If Debug key (F1) is pressed, draw a red outline around the entity
        if (m_input_system.m_keys_pressed.find(SDLK_F1) != m_input_system.m_keys_pressed.end()) {
            DrawDebugRect(texture, transform, rect);
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
            SDL_RenderTexture(renderer, layer.second, NULL, NULL);
        }
    }

    /**
     * @brief Determines if a texture at a given screen position is outside the screen bounds and should be culled
     * @param screen_position The position on the screen to check for culling
     * @param texture The texture to check for culling
     */
    bool RenderSystem::IsCulled(glm::vec2& screen_position, Texture& texture) {
        return screen_position.x + texture.m_size.x <= 0 ||
            screen_position.y + texture.m_size.y <= 0 ||
            screen_position.x >= m_renderer_size.x ||
            screen_position.y >= m_renderer_size.y;
    }

    /**
     * @brief Determines if an entity is outside the screen bounds and should be culled
     * @param entity EntityID to check for culling
     */
    bool RenderSystem::IsCulled(EntityID entity) {
        auto& transform = g_ecs.GetComponent<Transform2D>(entity);
        auto& texture = g_ecs.GetComponent<Texture>(entity);

        glm::vec2 screen_position = CalculateFinalPosition(transform, texture);

        return IsCulled(screen_position, texture);
    }

    glm::vec2 RenderSystem::CalculateFinalPosition(Transform2D& transform, Texture& texture) {
        // Calculate screen position based on camera
        glm::vec2 screen_position = m_camera_system.CalculateScreenPosition(transform.m_world_position);

        // TODO: Add adjustable anchor point support (top-left, center, bottom-right, etc...)
        // Center the texture on the position
        screen_position -= (texture.m_size * 0.5f);
        
        return screen_position;
    }

    /**
     * @brief Draws a red outline around the entity's texture for debugging purposes
     */
    void RenderSystem::DrawDebugRect(const Texture& texture, const Transform2D& transform, const SDL_FRect* rect) {
        SDL_Renderer* renderer = g_app.GetRenderer();

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Texture* debug_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                        SDL_TEXTUREACCESS_TARGET, static_cast<int>(texture.m_size.x), static_cast<int>(texture.m_size.y));
        SDL_FRect* debug_rect = new SDL_FRect({0, 0, texture.m_size.x, texture.m_size.y});
        SDL_SetRenderTarget(renderer, debug_texture);
        SDL_SetTextureBlendMode(debug_texture, SDL_BLENDMODE_BLEND);
        SDL_RenderRect(renderer, debug_rect);
        SDL_SetRenderTarget(renderer, m_layers[transform.m_layer]);
        SDL_RenderTextureRotated(renderer, debug_texture, NULL, rect,
            transform.m_world_rotation, NULL, SDL_FLIP_NONE);

        if (debug_texture) {
            SDL_DestroyTexture(debug_texture);
        }
        if (debug_rect) {
            delete debug_rect;
        }
    }
}