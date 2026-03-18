/**
 * @file interact_system.cpp
 * @author Daniel Parker
 * @brief System for managing and rendering UI elements.
 * @version 0.1
 * @date 2026-03-17
 *
 * @copyright Copyright (c) 2026
 */

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/defaults/components/ui/interactive.hpp>
#include <HotBeanEngine/defaults/components/ui/ui_rect.hpp>
#include <HotBeanEngine/defaults/systems/ui/interact_system.hpp>

namespace HBE::Default::Systems {
    using namespace Core;
    using namespace Components;
    using namespace Application::Events;

    void InteractSystem::OnEvent(SDL_Event &event) {
        for (auto &entity : m_entities) {
            auto &button = g_ecs.GetComponent<Interactive>(entity);
            auto &texture = g_ecs.GetComponent<Texture>(entity);

            auto mouse_buttons_pressed = g_app.GetInputEventListener().GetMouseButtonsPressed();

            // Only process click if we received a mouse click event and the left mouse button is currently pressed
            if (mouse_buttons_pressed.find(SDL_BUTTON_LEFT) == mouse_buttons_pressed.end()) {
                return;
            }

            // Check if button was clicked
            float mouse_x, mouse_y;
            SDL_GetMouseState(&mouse_x, &mouse_y);
            SDL_FPoint mouse_point = {mouse_x, mouse_y};

            // Check if using screen space
            if (g_ecs.HasComponent<UIRect>(entity)) {
                auto &ui_rect = g_ecs.GetComponent<UIRect>(entity);
                int screen_width, screen_height;
                SDL_GetRenderOutputSize(g_app.GetRenderer(), &screen_width, &screen_height);

                SDL_FRect button_rect = ui_rect.GetScreenBounds(screen_width, screen_height);
                if (SDL_PointInRectFloat(&mouse_point, &button_rect)) {
                    // Button was clicked - emit click event
                    g_app.GetEventManager().Emit(OnClickEvent{entity});
                }
            }
            else {
                // World space: use camera transforms
                auto &transform = g_ecs.GetComponent<Transform2D>(entity);

                for (auto &camera_entity : g_app.GetCameraManager().GetAllActiveCameras()) {
                    auto &camera = g_ecs.GetComponent<Camera>(camera_entity);
                    auto &camera_transform = g_ecs.GetComponent<Transform2D>(camera_entity);

                    auto screen_pos =
                        g_app.GetCameraManager().CalculateScreenPosition(camera, camera_transform, transform);

                    SDL_FRect button_rect = {screen_pos.x - (texture.m_size.x / 2),
                                             screen_pos.y - (texture.m_size.y / 2), texture.m_size.x, texture.m_size.y};

                    if (SDL_PointInRectFloat(&mouse_point, &button_rect)) {
                        // Button was clicked - emit click event
                        g_app.GetEventManager().Emit(OnClickEvent{entity});
                    }
                }
            }
        }
    }

    bool InteractSystem::DidMouseSweepThroughRect(const SDL_FRect &rect) const {
        float x1 = m_previous_mouse_position.x;
        float y1 = m_previous_mouse_position.y;
        float x2 = m_current_mouse_position.x;
        float y2 = m_current_mouse_position.y;

        if (x1 == x2 && y1 == y2) {
            return false;
        }

        return SDL_GetRectAndLineIntersectionFloat(&rect, &x1, &y1, &x2, &y2);
    }

    /**
     * Updates all UI element textures
     */
    void InteractSystem::OnUpdate() {
        SDL_GetMouseState(&m_current_mouse_position.x, &m_current_mouse_position.y);

        if (!m_has_mouse_position_sample) {
            m_previous_mouse_position = m_current_mouse_position;
            m_has_mouse_position_sample = true;
        }

        for (auto &entity : m_entities) {
            auto &button = g_ecs.GetComponent<Interactive>(entity);
            auto &texture = g_ecs.GetComponent<Texture>(entity);

            SDL_FPoint mouse_point = m_current_mouse_position;

            // Check if mouse is over button
            bool currently_hovered = false;
            bool swept_through_while_outside = false;

            // Check if using screen space
            if (g_ecs.HasComponent<UIRect>(entity)) {
                auto &ui_rect = g_ecs.GetComponent<UIRect>(entity);
                int screen_width, screen_height;
                SDL_GetRenderOutputSize(g_app.GetRenderer(), &screen_width, &screen_height);

                SDL_FRect button_rect = ui_rect.GetScreenBounds(screen_width, screen_height);
                currently_hovered = SDL_PointInRectFloat(&mouse_point, &button_rect);

                if (!currently_hovered && !button.m_mouse_hover) {
                    swept_through_while_outside = DidMouseSweepThroughRect(button_rect);
                }
            }
            else {
                // World space: check against camera transforms
                auto &transform = g_ecs.GetComponent<Transform2D>(entity);

                for (auto &camera_entity : g_app.GetCameraManager().GetAllActiveCameras()) {
                    auto &camera = g_ecs.GetComponent<Camera>(camera_entity);
                    auto &camera_transform = g_ecs.GetComponent<Transform2D>(camera_entity);

                    auto screen_pos =
                        g_app.GetCameraManager().CalculateScreenPosition(camera, camera_transform, transform);
                    SDL_FRect button_rect = {screen_pos.x - (texture.m_size.x / 2),
                                             screen_pos.y - (texture.m_size.y / 2), texture.m_size.x, texture.m_size.y};

                    if (SDL_PointInRectFloat(&mouse_point, &button_rect)) {
                        currently_hovered = true;
                        break;
                    }

                    if (!button.m_mouse_hover && DidMouseSweepThroughRect(button_rect)) {
                        swept_through_while_outside = true;
                    }
                }
            }

            if ((currently_hovered && !button.m_mouse_hover) || swept_through_while_outside) {
                g_app.GetEventManager().Emit(OnEnterEvent{entity});
                button.m_mouse_hover = true;
            }
            if (!currently_hovered && button.m_mouse_hover) {
                g_app.GetEventManager().Emit(OnExitEvent{entity});
                button.m_mouse_hover = false;
            }
        }

        m_previous_mouse_position = m_current_mouse_position;
    }
} // namespace HBE::Default::Systems