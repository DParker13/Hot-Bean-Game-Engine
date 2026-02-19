/**
 * @file checkbox.hpp
 * @author Daniel Parker (DParker13)
 * @brief Checkbox component. Used for storing checkbox state.
 * @version 0.1
 * @date 2025-11-02
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <SDL3_ttf/SDL_ttf.h>

#include <HotBeanEngine/defaults/components/ui/ui_element.hpp>
#include <HotBeanEngine/editor/iproperty_renderable.hpp>

#include <HotBeanEngine/editor/property_nodes/color.hpp>
#include <HotBeanEngine/editor/property_nodes/enum.hpp>
#include <HotBeanEngine/editor/property_nodes/int.hpp>
#include <HotBeanEngine/editor/property_nodes/string.hpp>

namespace HBE::Default::Components {

    struct Checkbox : public UIElement, public IPropertyRenderable {
        TTF_Font *m_font = nullptr; ///< Pointer to the TTF font object. Can be null if the font has not been loaded.
        SDL_Color m_foreground_color = {255, 255, 255, 255}; ///< The color of the text.
        SDL_Color m_background_color = {0, 0, 0, 255};       ///< The background color of the text.
        Uint32 m_size = 10;                                  ///< The size of the font.
        Uint32 m_style = TTF_STYLE_NORMAL;                   ///< The style of the font.
        Uint32 m_wrapping_width = 0;                         ///< The wrapping width of the text.
        std::string m_text = "default text";                 ///< The text to be rendered.

        DEFINE_NAME("Checkbox");
        Checkbox() : UIElement() {}

        void Deserialize(YAML::Node &node) override {
            if (node["text"]) {
                m_text = node["text"].as<std::string>();
            }

            if (node["foreground_color"]) {
                m_foreground_color = node["foreground_color"].as<SDL_Color>();
            }

            if (node["background_color"]) {
                m_background_color = node["background_color"].as<SDL_Color>();
            }

            if (node["size"]) {
                m_size = node["size"].as<int>();
            }

            if (node["style"]) {
                m_style = node["style"].as<int>();
            }

            if (node["wrapping_width"]) {
                m_wrapping_width = node["wrapping_width"].as<int>();
            }
        }

        void Serialize(YAML::Emitter &out) const override {
            if (!m_text.empty()) {
                out << YAML::Key << "text" << YAML::Value << m_text;
            }
            out << YAML::Key << "color" << YAML::Value << m_foreground_color;
            out << YAML::Key << "color" << YAML::Value << m_background_color;
            out << YAML::Key << "size" << YAML::Value << m_size;
            out << YAML::Key << "style" << YAML::Value << m_style;
            out << YAML::Key << "wrapping_width" << YAML::Value << m_wrapping_width;
        }

        /**
         * Gets the text of the Text component.
         *
         * This function gets the current text being rendered.
         *
         * @return The text being rendered.
         */
        std::string GetString() const { return m_text; }

        /**
         * Gets the C string representation of the text.
         *
         * This function is a convenience function that returns the C string representation of the text.
         * This is the same as calling GetString().c_str().
         *
         * @return A pointer to the C string representation of the text.
         */
        const char *GetChar() const { return m_text.data(); }

        void RenderProperties(int &id) override {
            PropertyNodes::String::RenderProperty(id, "Text", m_text);
            PropertyNodes::Color::RenderProperty(id, "Foreground Color", m_foreground_color);
            PropertyNodes::Color::RenderProperty(id, "Background Color", m_background_color);
            PropertyNodes::Enum::RenderProperty(id, "Font Style", m_style,
                                                {{TTF_STYLE_NORMAL, "Normal"},
                                                 {TTF_STYLE_BOLD, "Bold"},
                                                 {TTF_STYLE_ITALIC, "Italic"},
                                                 {TTF_STYLE_UNDERLINE, "Underline"},
                                                 {TTF_STYLE_STRIKETHROUGH, "Strikethrough"}});
            PropertyNodes::Int::RenderProperty(id, "Font Size", reinterpret_cast<int &>(m_size));
            PropertyNodes::Int::RenderProperty(id, "Wrapping Width", reinterpret_cast<int &>(m_wrapping_width));
        }
    };
} // namespace HBE::Default::Components