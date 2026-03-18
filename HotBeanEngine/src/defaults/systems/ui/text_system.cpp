/**
 * @file text_system.cpp
 * @author Daniel Parker
 * @brief System for text management
 * @version 0.1
 * @date 2026-03-17
 *
 * @copyright Copyright (c) 2026
 */

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/application/events/interactive_events.hpp>
#include <HotBeanEngine/defaults/components/ui/interactive.hpp>
#include <HotBeanEngine/defaults/components/ui/text.hpp>
#include <HotBeanEngine/defaults/components/ui/ui_rect.hpp>
#include <HotBeanEngine/defaults/systems/ui/text_system.hpp>

namespace HBE::Default::Systems {
    using namespace Core;
    using namespace Components;
    using namespace Application::Events;

    TextSystem::~TextSystem() {
        TTF_CloseFont(m_font); // This causes a segmentation fault on exit for some reason
        m_font = nullptr;
    }

    void TextSystem::OnStart() { SetupFont(); }

    void TextSystem::OnWindowResize(SDL_Event &event) {
        for (auto &entity : m_entities) {
            auto &texture = g_ecs.GetComponent<Texture>(entity);
            texture.MarkDirty();
        }
    }

    /**
     * Updates all UI element textures
     */
    void TextSystem::OnRender() {
        for (auto &entity : m_entities) {
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
    }

    void TextSystem::SetupFont() {
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