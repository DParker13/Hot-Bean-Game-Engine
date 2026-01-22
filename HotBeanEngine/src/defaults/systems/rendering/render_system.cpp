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
        CreateLayerTextureForEntity(entity);
    }

    /**
     * @brief Called when the window is resized
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
    }

    void RenderSystem::OnUpdate() {
        // Layers used this frame will be tracked in OnRender
        m_layers_used.clear();
    }
    
    /**
     * @brief Render each entity to its respective texture layer and then combine them on the screen
     */
    void RenderSystem::OnRender() {
        for (auto& entity : m_entities) {
            for (EntityID camera_entity : m_camera_system.GetAllActiveCameras()) {
                // TODO: Re-enable culling later when it works with multiple cameras
                // if (!m_camera_system.IsCulled(camera_entity, entity)) {
                //     auto& transform = g_ecs.GetComponent<Transform2D>(entity);
                //     m_layers_used.insert(transform.m_layer);
                    
                //     // Render entity to its respective texture layer
                //     RenderTextureToLayer(camera_entity, entity);
                // }

                auto& transform = g_ecs.GetComponent<Transform2D>(entity);
                m_layers_used.insert(transform.m_layer);
                
                // Render entity to its respective texture layer
                RenderTextureToLayer(camera_entity, entity);
            }
        }

        // Render all layers in order, back to front (layer 0 first, layer 1 second, etc...)
        RenderAllLayers();
    }

    /**
     * @brief Clears all the layer textures for the next frame and removes unused layers.
     */
    void RenderSystem::OnPostRender() {
        auto* renderer = g_app.GetRenderer();

        // Remove layers that were not used this frame
        for (auto i = m_layers.begin(); i != m_layers.end();) {
            if (m_layers_used.find(i->first) != m_layers_used.end()) {
                // Layer was used, keep i
                ++i;
            } else {
                // Layer was not used, remove it
                SDL_DestroyTexture(i->second);
                i = m_layers.erase(i);
            }
        }

        // Clear all layers with a transparent background
        for (auto& layer : m_layers) {
            SDL_SetRenderTarget(renderer, layer.second);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // Set draw color to fully transparent
            SDL_RenderClear(renderer);
        }
    }

    /**
     * @brief Creates a texture layer for the entity's layer if it doesn't already exist
     * @param entity EntityID to create layer for
     */
    void RenderSystem::CreateLayerTextureForEntity(EntityID entity) {
        auto& transform = g_ecs.GetComponent<Transform2D>(entity);

        // Skips layers that have already been created
        if (m_layers.find(transform.m_layer) != m_layers.end()) {
            return;
        }

        int renderer_w, renderer_h;
        SDL_GetRenderOutputSize(g_app.GetRenderer(), &renderer_w, &renderer_h);

        // Create texture the size of the renderer (screen)
        SDL_Texture* current_layer = SDL_CreateTexture(g_app.GetRenderer(), SDL_PIXELFORMAT_RGBA8888,
                                    SDL_TEXTUREACCESS_TARGET, renderer_w, renderer_h);

        if (current_layer == nullptr) {
            LOG(LoggingType::ERROR, "Failed to create layer texture! SDL_Error: " + std::string(SDL_GetError()));
            return;
        }

        // Set blend mode to allow for transparency between layers
        SDL_SetTextureBlendMode(current_layer, SDL_BLENDMODE_BLEND);

        // Store the texture in the map
        m_layers[transform.m_layer] = current_layer;
    }

    /**
     * @brief Render entity texture to its appropriate layer texture
     * @param entity EntityID to render to layer
     */
    void RenderSystem::RenderTextureToLayer(EntityID camera_entity, EntityID entity) {
        auto* renderer = g_app.GetRenderer();
        auto& transform = g_ecs.GetComponent<Transform2D>(entity);
        auto& texture = g_ecs.GetComponent<Texture>(entity);

        if (texture.m_texture == nullptr) {
            LOG(LoggingType::ERROR, "Entity " + std::to_string(entity) + " has no texture to render!");
            return;
        }

        if (m_layers.find(transform.m_layer) == m_layers.end()) {
            CreateLayerTextureForEntity(entity);
        }
        
        glm::vec2 screen_position = CalculateFinalPosition(camera_entity, entity);

        // Switch rendering target to current layer the entity is in
        SDL_SetRenderTarget(renderer, m_layers[transform.m_layer]);

        // Get camera zoom and apply to texture size
        float zoom = m_camera_system.GetZoom(camera_entity);
        glm::vec2 scaled_size = texture.m_size * zoom;

        // Get viewport and set as clip rect
        SDL_FRect viewport = m_camera_system.GetViewport(camera_entity);
        SDL_Rect clip_rect = {
            static_cast<int>(viewport.x),
            static_cast<int>(viewport.y),
            static_cast<int>(viewport.w),
            static_cast<int>(viewport.h)
        };
        
        // Set clip rectangle - anything outside this rect won't be rendered
        SDL_SetRenderClipRect(renderer, &clip_rect);
        
        // Create rect the size and position of the texture (stack allocation)
        SDL_FRect rect = {screen_position.x, screen_position.y, scaled_size.x, scaled_size.y};

        // Render texture to layer
        SDL_RenderTextureRotated(renderer, texture.m_texture, NULL, &rect,
            transform.m_world_rotation, NULL, SDL_FLIP_NONE);

        // TODO: Optimize debug rendering to not create/destroy texture and rect every frame?
        // If Debug key (F1) is pressed, draw a red outline around the entity
        if (g_app.GetInputEventListener().GetKeysPressed().find(SDLK_F1) != 
            g_app.GetInputEventListener().GetKeysPressed().end()) {
            DrawDebugRect(texture, transform, &rect);
        }

        // Clear clip rect (restore to full rendering area)
        SDL_SetRenderClipRect(renderer, NULL);
    }

    /**
     * @brief Renders all layers to the screen in order
     */
    void RenderSystem::RenderAllLayers() {
        auto* renderer = g_app.GetRenderer();

        // Ensure the render target is set to the screen
        SDL_SetRenderTarget(renderer, nullptr);

        // Render each layer in order, ensuring proper blending
        for (auto& layer : m_layers) {
            // Render the layer texture to the screen
            SDL_RenderTexture(renderer, layer.second, nullptr, nullptr);
        }
    }

    glm::vec2 RenderSystem::CalculateFinalPosition(EntityID camera_entity, EntityID entity) {
        // Calculate screen position based on camera
        auto& transform = g_ecs.GetComponent<Transform2D>(entity);
        auto& texture = g_ecs.GetComponent<Texture>(entity);

        glm::vec2 screen_position = m_camera_system.CalculateScreenPosition(camera_entity, entity);

        // Get zoom to calculate scaled size for centering
        float zoom = m_camera_system.GetZoom(camera_entity);
        glm::vec2 scaled_size = texture.m_size * zoom;

        // TODO: Add adjustable anchor point support (top-left, center, bottom-right, etc...)
        // Center the texture on the position
        screen_position -= (scaled_size * 0.5f);
        
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
        
        if (debug_texture == nullptr) {
            return;
        }
        
        SDL_FRect debug_rect = {0, 0, texture.m_size.x, texture.m_size.y};
        SDL_SetRenderTarget(renderer, debug_texture);
        SDL_SetTextureBlendMode(debug_texture, SDL_BLENDMODE_BLEND);
        SDL_RenderRect(renderer, &debug_rect);
        SDL_SetRenderTarget(renderer, m_layers[transform.m_layer]);
        SDL_RenderTextureRotated(renderer, debug_texture, NULL, rect,
            transform.m_world_rotation, NULL, SDL_FLIP_NONE);

        SDL_DestroyTexture(debug_texture);
    }
}