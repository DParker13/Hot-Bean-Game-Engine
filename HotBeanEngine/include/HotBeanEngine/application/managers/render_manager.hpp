/**
 * @file render_manager.hpp
 * @author Daniel Parker (DParker13)
 * @brief Manages render layers within the application.
 * @version 0.1
 * @date 2026-01-28
 *
 * @copyright Copyright (c) 2026
 */
#pragma once

#include <unordered_set>
#include <map>
#include <set>

#include <HotBeanEngine/application/managers/entity_lifecycle_listener.hpp>
#include <HotBeanEngine/application/managers/camera_manager.hpp>
#include <HotBeanEngine/defaults/components/miscellaneous/transform_2d.hpp>
#include <HotBeanEngine/defaults/components/rendering/texture.hpp>

namespace HBE::Application::Managers {
    class RenderManager : public IEntityLifecycleListener {
    private:
        std::shared_ptr<CameraManager> m_camera_manager;
        /**
         * @brief Map of layer indices to SDL_Texture pointers for offscreen rendering.
         */
        std::map<int, SDL_Texture *> m_layers;
        /**
         * @brief Cached set of entities that have Texture and Transform2D components.
         */
        std::set<EntityID> m_renderable_entities;

    public:
        RenderManager(std::shared_ptr<CameraManager> camera_manager) : m_camera_manager(camera_manager) {};

        /**
         * @brief Called when a component is added to an entity.
         * @param entity The entity ID that gained a component.
         */
        void OnComponentAdded(HBE::Core::EntityID entity);

        /**
         * @brief Called when a component is removed from an entity.
         * @param entity The entity ID that lost a component.
         */
        void OnComponentRemoved(HBE::Core::EntityID entity);
        /**
         * @brief Destructor. Cleans up all SDL_Texture layers.
         */
        ~RenderManager();

        /**
         * @brief Handles window resize events to update layer textures.
         * @param event The SDL window event.
         */
        void OnWindowResize(SDL_Event &event);

        /**
         * @brief Called every frame to render all entities managed by this system.
         */
        void OnRender();

        /**
         * @brief Called after rendering to clear and manage layer textures.
         */
        void OnPostRender();

        /**
         * @brief Get a copy of all current layer textures.
         * @return Map of layer indices to SDL_Texture pointers.
         */
        std::map<int, SDL_Texture *> GetAllLayers() const { return m_layers; }

    private:
        /**
         * @brief Creates a texture layer for the entity's layer if it doesn't already exist.
         * @param transform Entity transform component.
         */
        void CreateLayerTextureForEntity(const HBE::Default::Components::Transform2D &transform);

        /**
         * @brief Renders an entity's texture to its assigned layer.
         * @param camera Camera component.
         * @param camera_transform Camera transform component.
         * @param entity_transform Entity transform component.
         * @param texture Entity texture component.
         */
        void RenderTextureToLayer(const HBE::Default::Components::Camera &camera,
                                  const HBE::Default::Components::Transform2D &camera_transform,
                                  const HBE::Default::Components::Transform2D &entity_transform,
                                  const HBE::Default::Components::Texture &texture);

        /**
         * @brief Renders all layer textures to the screen in order.
         */
        void RenderAllLayers();

        /**
         * @brief Computes final screen position for an entity relative to a camera.
         * @param camera Camera component.
         * @param camera_transform Camera transform component.
         * @param entity_transform Entity transform component.
         * @param texture Entity texture component.
         * @return Screen-space position.
         */
        glm::vec2 CalculateFinalPosition(const HBE::Default::Components::Camera &camera,
                                         const HBE::Default::Components::Transform2D &camera_transform,
                                         const HBE::Default::Components::Transform2D &entity_transform,
                                         const HBE::Default::Components::Texture &texture);
    };
} // namespace HBE::Application::Managers