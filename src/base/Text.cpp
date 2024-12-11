#include "Text.h"

Text::Text(std::string text)
    : text(text) {
    font = TTF_OpenFont("../../assets/fonts/LT_Superior_Mono/LTSuperiorMono-Regular.ttf", 500);

    if (font == NULL) {
        SDL_Log("Couldn't load font: %s\n", SDL_GetError());
    }
    else {
        TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
        TTF_SetFontOutline(font, 0);
        TTF_SetFontKerning(font, 1);
        TTF_SetFontHinting(font, TTF_HINTING_MONO);

        foregroundCol = std::make_unique<SDL_Color>();
        foregroundCol->r = 255;
        foregroundCol->g = 255;
        foregroundCol->b = 255;
        foregroundCol->a = 255;
    }
}

Text::Text(Position<float> startingPos, std::string text)
    : Text(text) {
    SetPosition(startingPos);
}


void Text::OnUpdate(std::shared_ptr<float> deltaTime) {
    
}
void Text::OnRender(SDL_Surface* surface, SDL_Renderer* renderer) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Solid(font, text, *foregroundCol));
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    SDL_DestroyTexture(texture);
}