/**
 * @file render_system.hpp
 * @author Daniel Parker (DParker13)
 * @brief System for 2D rendering of textures.
 * @version 0.1
 * @date 2025-03-02
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <HotBeanEngine/defaults/systems/rendering/camera_system.hpp>

namespace HBE::Default::Systems {
    using namespace HBE::Core;
    using namespace HBE::Default::Components;

    /**
     * @class RenderSystem
     * @brief Handles 2D texture rendering for entities in the ECS.
     *
     * Renders sprites and textures with proper transforms, supporting multiple layers and cameras.
     * Processes entities with Transform2D and Texture components. Integrates with CameraSystem for viewport and zoom.
     */
    class RenderSystem : public ISystem {
    private:
        /**
         * @brief Reference to the CameraSystem for camera queries and transforms.
         */
        CameraSystem &m_camera_system;

        /**
         * @brief Map of layer indices to SDL_Texture pointers for offscreen rendering.
         */
        std::map<int, SDL_Texture *> m_layers;

        /**
         * @brief Set of layer indices used in the current frame.
         */
        std::unordered_set<int> m_layers_used;

    public:
        /**
         * @brief Defines the ECS signature for this system: requires Transform2D and Texture components.
         */
        DEFINE_SIGNATURE(RenderSystem, "Render System", Transform2D, Texture);

        /**
         * @brief Construct a new RenderSystem.
         * @param camera_system Reference to the CameraSystem.
         */
        RenderSystem(CameraSystem &camera_system) : m_camera_system(camera_system) {};

        /**
         * @brief Destructor. Cleans up all SDL_Texture layers.
         */
        ~RenderSystem();

        /**
         * @brief Called when an entity is added to the system.
         * @param entity The entity ID being added.
         */
        void OnEntityAdded(EntityID entity) override;

        /**
         * @brief Handles window resize events to update layer textures.
         * @param event The SDL window event.
         */
        void OnWindowResize(SDL_Event &event) override;

        /**
         * @brief Called every frame to update system state before rendering.
         */
        void OnUpdate() override;

        /**
         * @brief Called every frame to render all entities managed by this system.
         */
        void OnRender() override;

        /**
         * @brief Called after rendering to clear and manage layer textures.
         */
        void OnPostRender() override;

        /**
         * @brief Get a copy of all current layer textures.
         * @return Map of layer indices to SDL_Texture pointers.
         */
        std::map<int, SDL_Texture *> GetAllLayers() const { return m_layers; }

    private:
        /**
         * @brief Creates a texture layer for the entity's layer if it doesn't already exist.
         * @param entity EntityID to create layer for.
         */
        void CreateLayerTextureForEntity(EntityID entity);

        /**
         * @brief Render an entity's texture to its appropriate layer texture.
         * @param camera_entity Camera entity ID for viewport/zoom.
         * @param entity EntityID to render to layer.
         */
        void RenderTextureToLayer(EntityID camera_entity, EntityID entity);

        /**
         * @brief Renders all layers to the screen in order.
         */
        void RenderAllLayers();

        /**
         * @brief Calculates the final screen position for an entity given a camera.
         * @param camera_entity Camera entity ID.
         * @param entity EntityID to calculate position for.
         * @return The screen position as a glm::vec2.
         */
        glm::vec2 CalculateFinalPosition(EntityID camera_entity, EntityID entity);

        /**
         * @brief Draws a debug rectangle around the entity's texture.
         * @param texture The Texture component.
         * @param transform The Transform2D component.
         * @param rect The rectangle to draw.
         */
        void DrawDebugRect(const Texture &texture, const Transform2D &transform, const SDL_FRect *rect);
    };
} // namespace HBE::Default::Systems