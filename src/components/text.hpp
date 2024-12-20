#pragma once

#include <SDL_ttf.h>

namespace Components {
    struct Text : public IObject {
        TTF_Font* font;
        SDL_Color color;
        std::string text;

        void Init() {
            font = TTF_OpenFont("C:/Users/danie/Documents/GitHub/HotBeanEngine/assets/fonts/LT_Superior_Mono/LTSuperiorMono-Regular.ttf", 10);
            //font = TTF_OpenFont("../../assets/fonts/LT_Superior_Mono/LTSuperiorMono-Regular.ttf", 500);

            if (font == NULL) {
                SDL_Log("Couldn't load font: %s\n", SDL_GetError());
            }
            else {
                TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
                TTF_SetFontOutline(font, 0);
                TTF_SetFontKerning(font, 1);
                TTF_SetFontHinting(font, TTF_HINTING_MONO);

                color = SDL_Color();
                color.r = 255;
                color.g = 255;
                color.b = 255;
                color.a = 255;

                text = "";
            }
        }

        std::string ToString() const override {
            std::stringstream str;
            str << "    Component: Text \n";
            str << "      Text: " << text << "\n";
            str << "      Color: " << std::to_string(color.r) << ", " << std::to_string(color.g) << ", " << std::to_string(color.b) << ", " << std::to_string(color.a) << "\n";
            
            return str.str();
        }
    };
}