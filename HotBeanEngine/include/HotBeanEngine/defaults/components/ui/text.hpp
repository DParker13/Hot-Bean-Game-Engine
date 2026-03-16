/**
 * @file text.hpp
 * @author Daniel Parker (DParker13)
 * @brief Used for storing font, text, and styling.
 * @version 0.1
 * @date 2025-02-23
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <SDL3_ttf/SDL_ttf.h>

#include <HotBeanEngine/defaults/components/rendering/texture.hpp>
#include <HotBeanEngine/defaults/components/ui/ui_element.hpp>
#include <HotBeanEngine/editor/iproperty_renderable.hpp>

namespace HBE::Default::Components {

    struct Text : public UIElement, public Application::GUI::IPropertyRenderable {
        TTF_Font *m_font = nullptr; ///< Pointer to the TTF font object. Can be null if the font has not been loaded.
        SDL_Color m_foreground_color = {255, 255, 255, 255}; ///< The color of the text.
        SDL_Color m_background_color = {0, 0, 0, 255};       ///< The background color of the text.
        Uint32 m_size = 10;                                  ///< The size of the font.
        Uint32 m_style = TTF_STYLE_NORMAL;                   ///< The style of the font.
        Uint32 m_wrapping_width = 0;                         ///< The wrapping width of the text.
        std::string m_text = "default text";                 ///< The text to be rendered.

        DEFINE_NAME("Text");
        Text() : UIElement() {}

        void Deserialize(YAML::Node &node) override;
        void Serialize(YAML::Emitter &out) const override;
        void RenderProperties(int &id);
    };
} // namespace HBE::Default::Components