/**
 * @file ui_system.cpp
 * @author Daniel Parker
 * @brief System for managing and rendering UI elements.
 * @version 0.1
 * @date 2025-05-12
 * 
 * @copyright Copyright (c) 2025
 */

#include <HotBeanEngine/defaults/systems/ui/ui_system.hpp>

namespace HBE::Default::Systems {
    UISystem::~UISystem() {
        TTF_CloseFont(m_font); // This causes a segmentation fault on exit for some reason
        m_font = nullptr;
    }

    void UISystem::OnStart() {
        SetupFont();
    }

    void UISystem::OnWindowResize(SDL_Event& event) {
        for (auto& entity : m_entities) {
            auto& texture = g_ecs.GetComponent<Texture>(entity);
            texture.m_dirty = true;
        }
    }

    /**
     * Updates all UI element textures
     */
    void UISystem::OnUpdate() {
        for (auto& entity : m_entities) {
            auto& ui_element = g_ecs.GetComponent<UIElement>(entity);

            switch(ui_element.m_type) {
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
    }

    void UISystem::OnUpdateText(Entity entity) {
        auto* renderer = g_app.GetRenderer();

        auto& text = g_ecs.GetComponent<Text>(entity);
        auto& ui_element = g_ecs.GetComponent<UIElement>(entity);
        auto& texture = g_ecs.GetComponent<Texture>(entity);

        // Initialize font
        if (!text.m_font) {
            text.m_font = m_font;
        }
        
        // Update text texture if dirty
        if (texture.m_dirty) {
            SDL_Surface* text_surface = nullptr;

            // Render text to surface
            if (text.m_background_color.a == 0) {
                text_surface = TTF_RenderText_Solid_Wrapped(m_font, text.GetChar(), sizeof(text), text.m_foreground_color, text.m_wrapping_width);                
            }
            else {
                text_surface = TTF_RenderText_LCD_Wrapped(m_font, text.GetChar(), sizeof(text), text.m_foreground_color, text.m_background_color, text.m_wrapping_width);
            }

            if (!text_surface) {
                LOG(LoggingType::ERROR, "Couldn't render text: " + std::string(SDL_GetError()));
            }

            // Update texture with new surface
            if (text.m_font && text.GetString() != "" && text_surface) {
                texture.m_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
                texture.m_size = { text_surface->w, text_surface->h };
                SDL_SetTextureBlendMode(texture.m_texture, SDL_BLENDMODE_BLEND);
                texture.m_dirty = false;
            }

            if (text_surface) {
                SDL_DestroySurface(text_surface);
            }
        }
    }

    void UISystem::SetupFont() {
        m_font = TTF_OpenFont(_font_path.data(), 10);

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

    void UISystem::OnUpdateTextBox(Entity entity) {
        
    }

    void UISystem::OnUpdateImage(Entity entity) {}
    void UISystem::OnUpdateButton(Entity entity) {}
    void UISystem::OnUpdateSlider(Entity entity) {}
    void UISystem::OnUpdateDropdown(Entity entity) {}
    void UISystem::OnUpdateCheckbox(Entity entity) {}
    void UISystem::OnUpdateRadio(Entity entity) {}
}