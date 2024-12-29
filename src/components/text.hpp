#pragma once

#include <SDL_ttf.h>
#include <filesystem>

namespace Components {
    struct Text : public Object {
        TTF_Font* _font;
        SDL_Color _color;
        Uint32 _size;
        Uint32 _style;
        std::string _text;
        std::string _prevText;

        ~Text() {
            TTF_CloseFont(_font);
        }

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

        Text() {
            _size = 10;
            _style = TTF_STYLE_NORMAL;
            _font = nullptr;
            
            SDL_Color color = SDL_Color();
            color.r = 255;
            color.g = 255;
            color.b = 255;
            color.a = 255;

            _color = color;
            _text = "constructor";
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