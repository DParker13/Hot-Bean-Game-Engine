/**
 * @file text.hpp
 * @author Daniel Parker (DParker13)
 * @brief Text component. Used for keeping track of text.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "ui_element.hpp"

namespace Core::Components {

    /**
     * Represents a text component, which can be attached to an entity.
     */
    struct Text : public UIElement {
        public:
            TTF_Font* m_font = nullptr; ///< Pointer to the TTF font object. Can be null if the font has not been loaded.
            SDL_Color m_foreground_color = SDL_Color(); ///< The color of the text.
            SDL_Color m_background_color = SDL_Color(); ///< The background color of the text.
            Uint32 m_size = 10; ///< The size of the font.
            Uint32 m_style = TTF_STYLE_NORMAL; ///< The style of the font.
            Uint32 m_wrapping_width = 0; ///< The wrapping width of the text.

        private:
            std::string m_text = "default text"; ///< The text to be rendered.
        
        public:
            /**
             * @brief Construct a new Text component
             */
            Text() {
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

            std::string GetName() const override {
                return "Text";
            }

            void Deserialize(YAML::Node& node) override {
                UIElement::Deserialize(node);

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
                UIElement::Serialize(out);

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
             * Sets the text of the Text component.
             *
             * This function sets the text to render to the given string.
             * If the text is different from the current one, it sets a flag to update the text.
             *
             * @param text The text to be rendered.
             *
             * @return 0 if the text has changed, -1 otherwise.
             */
            int SetText(std::string text) {
                if (text != m_text) {
                    m_text = text;
                    m_dirty = true;

                    return 0;
                }

                return -1;
            }

            /**
             * Gets the text of the Text component.
             *
             * This function gets the current text being rendered.
             *
             * @return The text being rendered.
             */
            std::string GetString() const {
                return m_text;
            }

            /**
             * Gets the C string representation of the text.
             *
             * This function is a convenience function that returns the C string representation of the text.
             * This is the same as calling GetString().c_str().
             *
             * @return A pointer to the C string representation of the text.
             */
            const char*  GetChar() const {
                return m_text.data();
            }
    };
}