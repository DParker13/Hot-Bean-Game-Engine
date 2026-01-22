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
     * @brief Handles texture rendering for entities
     * 
     * Renders sprites and textures with proper transforms.
     * Processes entities with Transform2D and Texture components.
     */
    class RenderSystem : public ISystem {
    private:
        CameraSystem& m_camera_system;
        std::map<int, SDL_Texture*> m_layers;
        std::unordered_set<int> m_layers_used;
    
    public:
        DEFINE_SIGNATURE(RenderSystem, "Render System", Transform2D, Texture);
        RenderSystem(CameraSystem& camera_system)
            : m_camera_system(camera_system) {};
        ~RenderSystem();

        void OnEntityAdded(EntityID entity) override;
        void OnWindowResize(SDL_Event& event) override;
        void OnUpdate() override;
        void OnRender() override;
        void OnPostRender() override;

        std::map<int, SDL_Texture*> GetAllLayers() const { return m_layers; }

    private:
        void CreateLayerTextureForEntity(EntityID entity);
        void RenderTextureToLayer(EntityID camera_entity, EntityID entity);
        void RenderAllLayers();
        glm::vec2 CalculateFinalPosition(EntityID camera_entity, EntityID entity);
        void DrawDebugRect(const Texture& texture, const Transform2D& transform, const SDL_FRect* rect);
    };
}