#pragma once

#include <SDL_ttf.h>
#include <memory>
#include "Entity.h"

class Text : public Entity {
private:
    std::string text;
    std::unique_ptr<SDL_Color> foregroundCol;
    TTF_Font* font;

public:
    // Default constructor
    Text(std::string text);

    // Constructor taking a starting position
    Text(Position<float> startingPos, std::string text);

    void OnUpdate(std::shared_ptr<float> deltaTime) override;
    void OnRender(SDL_Surface* surface, SDL_Renderer* renderer) override;

};