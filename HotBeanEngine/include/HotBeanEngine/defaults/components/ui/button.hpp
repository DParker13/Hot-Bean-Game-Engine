/**
 * @file button.hpp
 * @author Daniel Parker (DParker13)
 * @brief Button component. Used for storing font, text, and styling.
 * @version 0.1
 * @date 2025-11-02
 * 
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <SDL3_ttf/SDL_ttf.h>

#include <HotBeanEngine/defaults/components/ui/ui_element.hpp>
#include <HotBeanEngine/editor_gui/iproperty_renderable.hpp>

#include <HotBeanEngine/editor_gui/property_nodes/color.hpp>
#include <HotBeanEngine/editor_gui/property_nodes/enum.hpp>
#include <HotBeanEngine/editor_gui/property_nodes/int.hpp>
#include <HotBeanEngine/editor_gui/property_nodes/string.hpp>

namespace HBE::Default::Components {
    struct Button : public UIElement, public HBE::Application::GUI::IPropertyRenderable {
        TTF_Font* m_font = nullptr; ///< Pointer to the TTF font object. Can be null if the font has not been loaded.
        SDL_Color m_foreground_color = SDL_Color(); ///< The color of the text.
        SDL_Color m_background_color = SDL_Color(); ///< The background color of the text.
        Uint32 m_size = 10; ///< The size of the font.
        Uint32 m_style = TTF_STYLE_NORMAL; ///< The style of the font.
        Uint32 m_wrapping_width = 0; ///< The wrapping width of the text.
        std::string m_text = "default text"; ///< The text to be rendered.

        DEFINE_NAME("Button");
        Button() {
            // Set the foreground color to white
            m_foreground_color = SDL_Color();
            m_foreground_color.r = 255;
            m_foreground_color.g = 255;
            m_foreground_color.b = 255;
            m_foreground_color.a = 255;

            // Set the background color to transparent
            m_background_color = SDL_Color();
            m_background_color.r = 0;
            m_background_color.g = 0;
            m_background_color.b = 0;
            m_background_color.a = 255;
        };

        void Deserialize(YAML::Node& node) override {
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

        void Serialize(YAML::Emitter& out) const override {
            if (!m_text.empty()) {
                out << YAML::Key << "text" << YAML::Value << m_text;
            }
            out << YAML::Key << "color" << YAML::Value << m_foreground_color;
            out << YAML::Key << "color" << YAML::Value << m_background_color;
            out << YAML::Key << "size" << YAML::Value << m_size;
            out << YAML::Key << "style" << YAML::Value << m_style;
            out << YAML::Key << "wrapping_width" << YAML::Value << m_wrapping_width;
        }

        void RenderProperties(int& id) override {
            HBE::Application::GUI::PropertyNodes::String::RenderProperty(id, "Text", m_text);
            HBE::Application::GUI::PropertyNodes::Color::RenderProperty(id, "Foreground Color", m_foreground_color);
            HBE::Application::GUI::PropertyNodes::Color::RenderProperty(id, "Background Color", m_background_color);
            HBE::Application::GUI::PropertyNodes::Enum::RenderProperty(id, "Font Style", m_style, {
                { TTF_STYLE_NORMAL, "Normal" },
                { TTF_STYLE_BOLD, "Bold" },
                { TTF_STYLE_ITALIC, "Italic" },
                { TTF_STYLE_UNDERLINE, "Underline" },
                { TTF_STYLE_STRIKETHROUGH, "Strikethrough" }
            });
            HBE::Application::GUI::PropertyNodes::Int::RenderProperty(id, "Font Size", reinterpret_cast<int&>(m_size));
            HBE::Application::GUI::PropertyNodes::Int::RenderProperty(id, "Wrapping Width", reinterpret_cast<int&>(m_wrapping_width));
        }
    };
}