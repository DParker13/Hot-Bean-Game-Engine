/**
 * @file editor_camera.hpp
 * @author Daniel Parker (DParker13)
 * @brief System for offsetting all transforms based on the editor camera.
 * @version 0.1
 * @date 2025-12-29
 * 
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <HotBeanEngine/core/all_core.hpp>
#include <HotBeanEngine/defaults/components/miscellaneous/transform_2d.hpp>
#include <HotBeanEngine/defaults/components/rendering/texture.hpp>

namespace HBE::Application::GUI {
    using namespace HBE::Core;

    struct EditorCamera {
        SDL_FRect m_camera = {0.0f, 0.0f, 1920.0f, 1080.0f};
        float m_camera_zoom = 1.0f;

        SDL_FRect GetViewport();
        glm::vec2 GetViewportCenter();
        glm::vec2 CalculateScreenPosition(EntityID entity);
        bool IsCulled(EntityID entity);
    };
}