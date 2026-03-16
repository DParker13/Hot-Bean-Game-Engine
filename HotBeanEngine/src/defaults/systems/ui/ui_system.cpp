/**
 * @file ui_system.cpp
 * @author Daniel Parker
 * @brief System for managing and rendering UI elements.
 * @version 0.1
 * @date 2025-05-12
 *
 * @copyright Copyright (c) 2025
 */

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/application/events/button_events.hpp>
#include <HotBeanEngine/defaults/components/ui/button.hpp>
#include <HotBeanEngine/defaults/components/ui/text.hpp>
#include <HotBeanEngine/defaults/components/ui/ui_rect.hpp>
#include <HotBeanEngine/defaults/systems/ui/ui_system.hpp>

namespace HBE::Default::Systems {
    using namespace Core;
    using namespace Components;
    using namespace Application::Events;

    UISystem::~UISystem() {
        TTF_CloseFont(m_font); // This causes a segmentation fault on exit for some reason
        m_font = nullptr;
    }

    void UISystem::OnStart() { SetupFont(); }

    void UISystem::OnWindowResize(SDL_Event &event) {
        for (auto &entity : m_entities) {
            auto &texture = g_ecs.GetComponent<Texture>(entity);
            texture.MarkDirty();
        }
    }

    void UISystem::OnEvent(SDL_Event &event) {
        for (auto &entity : m_entities) {
            auto &ui_element = g_ecs.GetComponent<UIElement>(entity);

            switch (ui_element.m_type) {
            case UIElement::UIType::Button:
                OnEventButton(entity);
                break;
            case UIElement::UIType::Slider:
                OnEventSlider(entity);
                break;
            case UIElement::UIType::Dropdown:
                OnEventDropdown(entity);
                break;
            case UIElement::UIType::Checkbox:
                OnEventCheckbox(entity);
                break;
            case UIElement::UIType::Radio:
                OnEventRadio(entity);
                break;
            }
        }
    }

    bool UISystem::DidMouseSweepThroughRect(const SDL_FRect &rect) const {
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
    void UISystem::OnUpdate() {
        float mouse_x, mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        m_current_mouse_position = {mouse_x, mouse_y};

        if (!m_has_mouse_position_sample) {
            m_previous_mouse_position = m_current_mouse_position;
            m_has_mouse_position_sample = true;
        }

        for (auto &entity : m_entities) {
            auto &ui_element = g_ecs.GetComponent<UIElement>(entity);

            switch (ui_element.m_type) {
            case UIElement::UIType::Text:
                OnUpdateText(entity);
                break;
            case UIElement::UIType::TextBox:
                OnUpdateTextBox(entity);
                break;
            case UIElement::UIType::Image:
                OnUpdateImage(entity);
                break;
            case UIElement::UIType::Button:
                OnUpdateButton(entity);
                break;
            case UIElement::UIType::Slider:
                OnUpdateSlider(entity);
                break;
            case UIElement::UIType::Dropdown:
                OnUpdateDropdown(entity);
                break;
            case UIElement::UIType::Checkbox:
                OnUpdateCheckbox(entity);
                break;
            case UIElement::UIType::Radio:
                OnUpdateRadio(entity);
                break;
            }
        }

        m_previous_mouse_position = m_current_mouse_position;
    }

    /**
     * Updates all UI element textures
     */
    void UISystem::OnRender() {
        for (auto &entity : m_entities) {
            auto &ui_element = g_ecs.GetComponent<UIElement>(entity);

            switch (ui_element.m_type) {
            case UIElement::UIType::Text:
                OnRenderText(entity);
                break;
            case UIElement::UIType::TextBox:
                OnRenderTextBox(entity);
                break;
            case UIElement::UIType::Image:
                OnRenderImage(entity);
                break;
            case UIElement::UIType::Button:
                OnRenderButton(entity);
                break;
            case UIElement::UIType::Slider:
                OnRenderSlider(entity);
                break;
            case UIElement::UIType::Dropdown:
                OnRenderDropdown(entity);
                break;
            case UIElement::UIType::Checkbox:
                OnRenderCheckbox(entity);
                break;
            case UIElement::UIType::Radio:
                OnRenderRadio(entity);
                break;
            }
        }
    }

    /**
     * @brief Handles button click events
     * @todo Implement proper event handling for buttons (currently just logs clicks) and other UI elements
     * @todo Implement hover and active states for buttons and other interactive UI elements
     * @todo Render UI elements without camera transformations (currently they are rendered in world space, which is not
     * ideal for UI) and implement a proper UI rendering pipeline
     *
     * @param entity The entity ID of the button that was clicked
     */
    void UISystem::OnEventButton(EntityID entity) {
        auto &button = g_ecs.GetComponent<Button>(entity);
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
                g_app.GetEventManager().Emit(ButtonClickEvent{entity});
            }
        }
        else {
            // World space: use camera transforms
            auto &transform = g_ecs.GetComponent<Transform2D>(entity);

            for (auto &camera_entity : g_app.GetCameraManager().GetAllActiveCameras()) {
                auto &camera = g_ecs.GetComponent<Camera>(camera_entity);
                auto &camera_transform = g_ecs.GetComponent<Transform2D>(camera_entity);

                auto screen_pos = g_app.GetCameraManager().CalculateScreenPosition(camera, camera_transform, transform);

                SDL_FRect button_rect = {screen_pos.x - (texture.m_size.x / 2), screen_pos.y - (texture.m_size.y / 2),
                                         texture.m_size.x, texture.m_size.y};

                if (SDL_PointInRectFloat(&mouse_point, &button_rect)) {
                    // Button was clicked - emit click event
                    g_app.GetEventManager().Emit(ButtonClickEvent{entity});
                }
            }
        }
    }

    void UISystem::OnEventSlider(EntityID entity) {}
    void UISystem::OnEventDropdown(EntityID entity) {}
    void UISystem::OnEventCheckbox(EntityID entity) {}
    void UISystem::OnEventRadio(EntityID entity) {}

    void UISystem::OnUpdateText(EntityID entity) {}
    void UISystem::OnUpdateTextBox(EntityID entity) {}
    void UISystem::OnUpdateImage(EntityID entity) {}
    void UISystem::OnUpdateButton(EntityID entity) {
        auto &button = g_ecs.GetComponent<Button>(entity);
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

            if (!currently_hovered && !button.m_was_hovered_last_frame) {
                swept_through_while_outside = DidMouseSweepThroughRect(button_rect);
            }
        }
        else {
            // World space: check against camera transforms
            auto &transform = g_ecs.GetComponent<Transform2D>(entity);

            for (auto &camera_entity : g_app.GetCameraManager().GetAllActiveCameras()) {
                auto &camera = g_ecs.GetComponent<Camera>(camera_entity);
                auto &camera_transform = g_ecs.GetComponent<Transform2D>(camera_entity);

                auto screen_pos = g_app.GetCameraManager().CalculateScreenPosition(camera, camera_transform, transform);
                SDL_FRect button_rect = {screen_pos.x - (texture.m_size.x / 2), screen_pos.y - (texture.m_size.y / 2),
                                         texture.m_size.x, texture.m_size.y};

                if (SDL_PointInRectFloat(&mouse_point, &button_rect)) {
                    currently_hovered = true;
                    break;
                }

                if (!button.m_was_hovered_last_frame && DidMouseSweepThroughRect(button_rect)) {
                    swept_through_while_outside = true;
                }
            }
        }

        // Emit events on state transitions
        button.m_mouse_hover = currently_hovered;

        if (currently_hovered && !button.m_was_hovered_last_frame) {
            g_app.GetEventManager().Emit(ButtonEnterEvent{entity});
        }
        if (!currently_hovered && button.m_was_hovered_last_frame) {
            g_app.GetEventManager().Emit(ButtonExitEvent{entity});
        }
        if (swept_through_while_outside) {
            g_app.GetEventManager().Emit(ButtonEnterEvent{entity});
            g_app.GetEventManager().Emit(ButtonExitEvent{entity});
        }

        // Update last frame hover state for next update
        button.m_was_hovered_last_frame = button.m_mouse_hover;
    }
    void UISystem::OnUpdateSlider(EntityID entity) {}
    void UISystem::OnUpdateDropdown(EntityID entity) {}
    void UISystem::OnUpdateCheckbox(EntityID entity) {}
    void UISystem::OnUpdateRadio(EntityID entity) {}

    void UISystem::OnRenderText(EntityID entity) {
        auto &text = g_ecs.GetComponent<Text>(entity);
        auto &texture = g_ecs.GetComponent<Texture>(entity);

        // Initialize font
        if (!text.m_font) {
            text.m_font = m_font;
        }

        // Update text texture if dirty
        if (texture.IsDirty() || text.IsDirty()) {
            SDL_Surface *text_surface = nullptr;

            // Render text to surface
            if (text.m_background_color.a == 0) {
                text_surface = TTF_RenderText_Solid_Wrapped(m_font, text.m_text.c_str(), 0, text.m_foreground_color,
                                                            text.m_wrapping_width);
            }
            else {
                text_surface = TTF_RenderText_LCD_Wrapped(m_font, text.m_text.c_str(), 0, text.m_foreground_color,
                                                          text.m_background_color, text.m_wrapping_width);
            }

            if (!text_surface) {
                LOG(LoggingType::ERROR, "Couldn't render text: " + std::string(SDL_GetError()));
                return;
            }

            // Update texture with new surface
            if (text.m_font && text.m_text != "") {
                texture.m_texture = SDL_CreateTextureFromSurface(g_app.GetRenderer(), text_surface);
                texture.m_size = {text_surface->w, text_surface->h};
                SDL_SetTextureBlendMode(texture.m_texture, SDL_BLENDMODE_BLEND);
                texture.MarkClean();
                text.MarkClean();
            }

            SDL_DestroySurface(text_surface);
        }
    }

    void UISystem::OnRenderTextBox(EntityID entity) {}
    void UISystem::OnRenderImage(EntityID entity) {}
    void UISystem::OnRenderButton(EntityID entity) { OnRenderText(entity); }
    void UISystem::OnRenderSlider(EntityID entity) {}
    void UISystem::OnRenderDropdown(EntityID entity) {}
    void UISystem::OnRenderCheckbox(EntityID entity) {}
    void UISystem::OnRenderRadio(EntityID entity) {}

    void UISystem::SetupFont() {
        m_font = TTF_OpenFont(m_font_path.data(), 10);

        if (!m_font) {
            LOG(LoggingType::ERROR, "Couldn't load font: " + std::string(SDL_GetError()));
        }
        else {
            TTF_SetFontStyle(m_font, TTF_STYLE_NORMAL);
            TTF_SetFontOutline(m_font, 0);
            TTF_SetFontKerning(m_font, 1);
            TTF_SetFontHinting(m_font, TTF_HINTING_MONO);
        }
    }
} // namespace HBE::Default::Systems