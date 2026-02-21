#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/application/managers/render_manager.hpp>

namespace HBE::Application::Managers {
    using HBE::Default::Components::Texture;
    using HBE::Default::Components::Transform2D;

    RenderManager::RenderManager(std::shared_ptr<CameraManager> camera_manager) : m_camera_manager(camera_manager) {
        // Listen for changes to Texture and Transform2D components to track renderable entities
        ListenForComponents({g_ecs.GetComponentID<Texture>(), g_ecs.GetComponentID<Transform2D>()});
    }

    /**
     * @brief Destructor. Cleans up all SDL_Texture layers.
     */
    RenderManager::~RenderManager() {
        // Clean up each texture layer
        for (const auto &layer : m_layers) {
            SDL_DestroyTexture(layer.second);
        }
    }

    /**
     * @brief Called when the window is resized
     * @param event The SDL window event
     */
    void RenderManager::OnWindowResize(SDL_Event &event) {
        // Destroy all texture layers to be recreated with the new renderer size
        for (const auto &layer : m_layers) {
            SDL_DestroyTexture(layer.second);
        }
        m_layers.clear();

        int new_w = event.window.data1;
        int new_h = event.window.data2;
        SDL_SetRenderLogicalPresentation(g_app.GetRenderer(), new_w, new_h, SDL_LOGICAL_PRESENTATION_DISABLED);
        SDL_SetRenderViewport(g_app.GetRenderer(), nullptr);
    }

    /**
     * @brief Render each entity to its respective texture layer for each camera, then combine all layers on the screen.
     *
     * Iterates over cached renderable entities and all active cameras, rendering each entity to the appropriate layer
     * texture. Finally, all layers are rendered to the screen in order.
     */
    void RenderManager::OnRender() {
        if (g_app.GetStateManager().IsState(ApplicationState::Playing)) {
            for (EntityID camera_entity : m_camera_manager->GetAllActiveCameras()) {
                auto &camera = g_ecs.GetComponent<Camera>(camera_entity);
                auto &camera_transform = g_ecs.GetComponent<Transform2D>(camera_entity);

                // Use cached set instead of GetEntitiesWithComponents for performance
                for (EntityID entity : m_renderable_entities) {
                    auto &transform = g_ecs.GetComponent<Transform2D>(entity);
                    auto &texture = g_ecs.GetComponent<Texture>(entity);
                    RenderTextureToLayer(camera, camera_transform, transform, texture);
                }
            }
        }
        else {
            // In editor, render all cached entities using the editor camera
            for (EntityID entity : m_renderable_entities) {
                auto &transform = g_ecs.GetComponent<Transform2D>(entity);
                auto &texture = g_ecs.GetComponent<Texture>(entity);
                RenderTextureToLayer(g_app.GetEditorGUI().GetEditorCamera(),
                                     g_app.GetEditorGUI().GetEditorCameraTransform(), transform, texture);
            }
        }

        // Render all layers in order, back to front (layer 0 first, layer 1 second, etc...)
        RenderAllLayers();
    }

    /**
     * @brief Clears all the layer textures for the next frame and removes unused layers.
     *
     * Removes any layer textures that were not used this frame, and clears all remaining layers to transparent.
     */
    void RenderManager::OnPostRender() {
        auto *renderer = g_app.GetRenderer();

        // Clear all layers with a transparent background
        for (auto &layer : m_layers) {
            SDL_SetRenderTarget(renderer, layer.second);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // Set draw color to fully transparent
            SDL_RenderClear(renderer);
        }
    }

    std::map<int, SDL_Texture *> RenderManager::GetAllLayers() const { return m_layers; }

    /**
     * @brief Called when a tracked component (Transform2D or Texture) is added to an entity.
     * If entity has both required components, it's added to the renderable cache.
     * @param component Pointer to the component that was added.
     * @param entity The entity ID that gained a component.
     */
    void RenderManager::OnComponentAdded(HBE::Core::IComponent *component, HBE::Core::EntityID entity) {
        m_renderable_entities.insert(entity);
    }

    /**
     * @brief Called when a tracked component is removed from an entity.
     * Removes entity from renderable cache.
     * @param entity The entity ID that lost a component.
     */
    void RenderManager::OnComponentRemoved(HBE::Core::EntityID entity) { m_renderable_entities.erase(entity); }

    /**
     * @brief Creates a texture layer for the entity's layer if it doesn't already exist.
     * @param transform Entity transform component.
     *
     * Allocates a new SDL_Texture for the layer if not present, sized to the renderer output.
     * Sets blend mode for transparency and stores the texture in the layer map.
     */
    void RenderManager::CreateLayerTextureForEntity(const Transform2D &transform) {
        // Skips layers that have already been created
        if (m_layers.find(transform.m_layer) != m_layers.end()) {
            return;
        }

        int renderer_w, renderer_h;
        SDL_GetRenderOutputSize(g_app.GetRenderer(), &renderer_w, &renderer_h);

        // Create texture the size of the renderer (screen)
        SDL_Texture *current_layer = SDL_CreateTexture(g_app.GetRenderer(), SDL_PIXELFORMAT_RGBA8888,
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
     * @brief Render an entity's texture to its appropriate layer texture for a given camera.
     * @param camera Camera component.
     * @param camera_transform Camera transform component.
     * @param entity_transform Entity transform component.
     * @param texture Entity texture component.
     *
     * Sets the render target to the entity's layer, applies camera zoom and viewport, and renders the texture.
     * If debug mode is enabled (F1), draws a debug rectangle around the entity.
     */
    void RenderManager::RenderTextureToLayer(const Camera &camera, const Transform2D &camera_transform,
                                             const Transform2D &entity_transform, const Texture &texture) {
        auto *renderer = g_app.GetRenderer();

        if (texture.m_texture == nullptr) {
            LOG(LoggingType::ERROR, "Entity has no texture to render!");
            return;
        }

        if (m_layers.find(entity_transform.m_layer) == m_layers.end()) {
            CreateLayerTextureForEntity(entity_transform);
        }

        glm::vec2 screen_position = CalculateFinalPosition(camera, camera_transform, entity_transform, texture);

        // Switch rendering target to current layer the entity is in
        SDL_SetRenderTarget(renderer, m_layers[entity_transform.m_layer]);

        // Get camera zoom and apply to texture size
        float zoom = m_camera_manager->GetZoom(camera);
        glm::vec2 scaled_size = texture.m_size * zoom;

        // Get viewport and set as clip rect
        SDL_FRect viewport = m_camera_manager->GetViewport(camera);
        SDL_Rect clip_rect = {static_cast<int>(viewport.x), static_cast<int>(viewport.y), static_cast<int>(viewport.w),
                              static_cast<int>(viewport.h)};

        // Set clip rectangle - anything outside this rect won't be rendered
        SDL_SetRenderClipRect(renderer, &clip_rect);

        // Create rect the size and position of the texture (stack allocation)
        SDL_FRect rect = {screen_position.x, screen_position.y, scaled_size.x, scaled_size.y};

        // Render texture to layer
        SDL_RenderTextureRotated(renderer, texture.m_texture, NULL, &rect, entity_transform.m_world_rotation, NULL,
                                 SDL_FLIP_NONE);

        // Clear clip rect (restore to full rendering area)
        SDL_SetRenderClipRect(renderer, NULL);
    }

    /**
     * @brief Renders all layers to the screen in order, ensuring proper blending.
     *
     * Sets the render target to the screen and draws each layer texture in order.
     */
    void RenderManager::RenderAllLayers() {
        auto *renderer = g_app.GetRenderer();

        // Ensure the render target is set to the screen
        SDL_SetRenderTarget(renderer, nullptr);

        // Render each layer in order, ensuring proper blending
        for (auto &layer : m_layers) {
            // Render the layer texture to the screen
            SDL_RenderTexture(renderer, layer.second, nullptr, nullptr);
        }
    }

    /**
     * @brief Calculates the final screen position using Camera and Transform2D components directly.
     * @param camera Camera component.
     * @param camera_transform Camera transform component.
     * @param entity_transform Entity transform component.
     * @param texture Entity texture component.
     * @return The screen position as a glm::vec2.
     *
     * Uses the camera's transform and zoom to compute the centered position for the entity's texture.
     */
    glm::vec2 RenderManager::CalculateFinalPosition(const Camera &camera, const Transform2D &camera_transform,
                                                    const Transform2D &entity_transform, const Texture &texture) {
        glm::vec2 screen_position =
            m_camera_manager->CalculateScreenPosition(camera, camera_transform, entity_transform);
        float zoom = m_camera_manager->GetZoom(camera);
        glm::vec2 scaled_size = texture.m_size * zoom;

        // TODO: Add adjustable anchor point support (top-left, center, bottom-right, etc...)
        // Center the texture on the position
        screen_position -= (scaled_size * 0.5f);

        return screen_position;
    }
} // namespace HBE::Application::Managers