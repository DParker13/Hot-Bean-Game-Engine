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

#include <HotBeanEngine/defaults/systems/input/input_system.hpp>
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
        InputSystem& m_input_system;
        CameraSystem& m_camera_system;
        std::map<int, SDL_Texture*> m_layers;
        std::map<int, bool> m_layer_is_empty;
        glm::ivec2 m_renderer_size = {0.0f, 0.0f};
    
    public:
        DEFINE_SIGNATURE(RenderSystem, "Render System", Transform2D, Texture);
        RenderSystem(InputSystem& input_system, CameraSystem& camera_system)
            : m_input_system(input_system), m_camera_system(camera_system) {};
        ~RenderSystem();

        void OnEntityAdded(EntityID entity) override;
        void OnWindowResize(SDL_Event& event) override;
        void OnStart() override;
        void OnUpdate() override;
        void OnRender() override;
        void OnPostRender() override;

    private:
        void CreateTextureLayers();
        void CreateTextureLayerForEntity(EntityID entity);
        void UpdateRendererSize();
        void RenderTextureToLayer(EntityID entity);
        void RenderAllLayers();
        bool IsCulled(glm::vec2& screen_position, Texture& texture);
        bool IsCulled(EntityID entity);
        glm::vec2 CalculateFinalPosition(Transform2D& transform, Texture& texture);
        void DrawDebugRect(const Texture& texture, const Transform2D& transform, const SDL_FRect* rect);
    };
}