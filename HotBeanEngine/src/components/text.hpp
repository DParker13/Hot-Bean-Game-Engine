/**
 * @file text.h
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

namespace Components {

    /**
     * Represents a text component, which can be attached to an entity.
     */
    struct Text : public UIElement {
        public:
            TTF_Font* _font = nullptr; ///< Pointer to the TTF font object. Can be null if the font has not been loaded.
            SDL_Color _color = SDL_Color(); ///< The color of the text.
            Uint32 _size = 10; ///< The size of the font.
            Uint32 _style = TTF_STYLE_NORMAL; ///< The style of the font.
            Uint32 _wrapping_width = 0; ///< The wrapping width of the text.

        private:
            std::string _text = "default text"; ///< The text to be rendered.
        
        public:
            /**
             * @brief Construct a new Text component
             */
            Text() {
                _color = SDL_Color();
                _color.r = 255;
                _color.g = 255;
                _color.b = 255;
                _color.a = 255;
            };

            /**
             * @brief Destroy the Text component
             */
            ~Text() = default;

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
                if (text != _text) {
                    _text = text;
                    _dirty = true;

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
                return _text;
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
                return _text.data();
            }

            std::string ToString() const override {
                std::stringstream str;
                str << "    Component: Text \n";
                str << "      Text: " << _text << "\n";
                str << "      Color: " << std::to_string(_color.r) << ", " << std::to_string(_color.g) << ", " << std::to_string(_color.b) << ", " << std::to_string(_color.a) << "\n";
                
                return str.str();
            }
    };
}