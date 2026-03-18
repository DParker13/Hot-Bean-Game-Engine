/**
 * @file slider.hpp
 * @author Daniel Parker (DParker13)
 * @brief Slider component. Used for storing slider properties.
 * @version 0.1
 * @date 2025-11-02
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <SDL3_ttf/SDL_ttf.h>

#include <HotBeanEngine/core/component.hpp>
#include <HotBeanEngine/editor/iproperty_renderable.hpp>

namespace HBE::Default::Components {

    struct Slider : public Core::IComponent, public Application::GUI::IPropertyRenderable {
        TTF_Font *m_font = nullptr; ///< Pointer to the TTF font object. Can be null if the font has not been loaded.
        SDL_Color m_foreground_color = {255, 255, 255, 255}; ///< The color of the text.
        SDL_Color m_background_color = {0, 0, 0, 255};       ///< The background color of the text.
        Uint32 m_size = 10;                                  ///< The size of the font.
        Uint32 m_style = TTF_STYLE_NORMAL;                   ///< The style of the font.
        Uint32 m_wrapping_width = 0;                         ///< The wrapping width of the text.
        std::string m_text = "default text";                 ///< The text to be rendered.

        DEFINE_NAME("Slider");
        Slider() = default;
        ~Slider() = default;

        void Deserialize(YAML::Node &node) override;
        void Serialize(YAML::Emitter &out) const override;

        /**
         * Gets the text of the Text component.
         *
         * This function gets the current text being rendered.
         *
         * @return The text being rendered.
         */
        std::string GetString() const;

        /**
         * Gets the C string representation of the text.
         *
         * This function is a convenience function that returns the C string representation of the text.
         * This is the same as calling GetString().c_str().
         *
         * @return A pointer to the C string representation of the text.
         */
        const char *GetChar() const;

        void RenderProperties(int &id) override;
    };
} // namespace HBE::Default::Components