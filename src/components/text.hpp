#pragma once

#include <SDL_ttf.h>

namespace Components {
    struct Text : public IObject {
        TTF_Font* _font;
        SDL_Color _color;
        Uint32 _size;
        Uint32 _style;
        std::string _text;

        Text(std::string text, Uint32 size, Uint32 style, SDL_Color color) {
            assert(size > 0 && "Font size must be greater than 0.");
            assert((style & ~(TTF_STYLE_NORMAL | TTF_STYLE_BOLD | TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE | TTF_STYLE_STRIKETHROUGH)) == 0);

            _size = size;
            _style = style;

            _font = TTF_OpenFont("C:/Users/danie/Documents/GitHub/HotBeanEngine/assets/fonts/LT_Superior_Mono/LTSuperiorMono-Regular.ttf", _size);

            if (_font == NULL) {
                SDL_Log("Couldn't load font: %s\n", SDL_GetError());
            }
            else {
                TTF_SetFontStyle(_font, _style);
                TTF_SetFontOutline(_font, 0);
                TTF_SetFontKerning(_font, 1);
                TTF_SetFontHinting(_font, TTF_HINTING_MONO);

                _color = color;
                _text = text;
            }
        }

        Text(std::string text, Uint32 size, SDL_Color color) {
            Text(text, size, TTF_STYLE_NORMAL, color);
        }

        Text(std::string text, Uint32 size, Uint32 style) {
            SDL_Color color = SDL_Color();
            color.r = 255;
            color.g = 255;
            color.b = 255;
            color.a = 255;

            Text(text, size, style, color);
        }

        Text(std::string text, Uint32 size) {
            Text(text, size, TTF_STYLE_NORMAL);
        }

        Text(Uint32 size) {
            Text("", size);
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