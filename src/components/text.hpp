/**
 * @file text.hpp
 * @brief Definition of the Text component, which can be attached to an entity.
 */

#pragma once

#include <SDL_ttf.h>
#include <vector>
#include <filesystem>

namespace Components {

    /**
     * Represents a text component, which can be attached to an entity.
     */
    class Text : public Object {
        public:
            TTF_Font* _font = nullptr; /**< A pointer to the TTF font object. Can be null if the font has not been loaded. */
            SDL_Surface* _surface = nullptr; /**< A pointer to the SDL surface object. Can be null if the surface has not been created. */
            SDL_Color _color = SDL_Color(); /**< The color of the text, represented as an SDL color struct. */
            Uint32 _size = 10; /**< The size of the font, represented as an unsigned 32-bit integer. */
            Uint32 _style = TTF_STYLE_NORMAL; /**< The style of the font, represented as an unsigned 32-bit integer. */
            bool _text_updated = false; /**< A flag indicating whether the text has been updated since the last render. */

        private:
            std::string _text = "default text"; /**< The text to be rendered. */
        
        public:
            /**
             * Destructor for the Text class.
             *
             * This function destroys the SDL_Surface and SDL_FontTTF.
             */
            ~Text() {
                SDL_FreeSurface(_surface);
                TTF_CloseFont(_font);
            }

            /**
             * Default constructor for the Text class.
             *
             * This constructor initializes the text color to white with full opacity.
             */
            Text() {
                _color = SDL_Color();
                _color.r = 255;
                _color.g = 255;
                _color.b = 255;
                _color.a = 255;
            };

            /**
             * Constructor for the Text class.
             *
             * This constructor initializes the text properties. The font size must be greater than 0.
             * The font style must be one of the following: TTF_STYLE_NORMAL, TTF_STYLE_BOLD, TTF_STYLE_ITALIC, TTF_STYLE_UNDERLINE, TTF_STYLE_STRIKETHROUGH.
             * The font path must exist.
             *
             * @param text The text to be rendered.
             * @param size The size of the font in pixels.
             * @param style The style of the font.
             * @param color The color of the text.
             */
            Text(std::string text, Uint32 size, Uint32 style, SDL_Color color) {
                assert(size > 0 && "Font size must be greater than 0.");
                assert((style & ~(TTF_STYLE_NORMAL | TTF_STYLE_BOLD | TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE | TTF_STYLE_STRIKETHROUGH)) == 0);

                _size = size;
                _style = style;

                auto fontPath = std::filesystem::current_path().parent_path() / "assets" / "fonts" / "LT_Superior_Mono" / "LTSuperiorMono-Regular.ttf";
                assert(std::filesystem::exists(fontPath) && "Font path invalid!");

                // This shouldn't be done in the constructor. This might be a waste of memory.
                _font = TTF_OpenFont(fontPath.string().data(), _size);

                if (!_font) {
                    SDL_Log("Couldn't load font: %s\n", SDL_GetError());
                }
                else {
                    TTF_SetFontStyle(_font, _style);
                    TTF_SetFontOutline(_font, 0);
                    TTF_SetFontKerning(_font, 1);
                    TTF_SetFontHinting(_font, TTF_HINTING_MONO);

                    SDL_Color color = SDL_Color();
                    color.r = 255;
                    color.g = 255;
                    color.b = 255;
                    color.a = 255;

                    _color = color;
                    _text = text;
                }
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
                if (text != _text) {
                    _text = text;
                    _text_updated = true;

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