#include "Cell.h"
#include <iostream>
#include <vector>


Cell::Cell(std::shared_ptr<FastNoiseLite> noise, std::shared_ptr<Uint8> spacing, std::shared_ptr<Uint8> maxHeight) :
    noise(noise), spacing(spacing), maxHeight(maxHeight) {
}



void Cell::OnUpdate() {
    //setPosition(X + 1, Y, Z);
}

void Cell::OnRender(SDL_Surface* surface, SDL_Renderer* renderer) {
    Uint8 colorVal = mapNoiseToColor(noise->GetNoise(X, Y));
    SDL_Color color = { colorVal, colorVal, colorVal, 0xFF };
    createRect(surface, renderer, &color);
}

// Function to fill a rectangle on an SDL_Surface
void Cell::createRect(SDL_Surface* surface, SDL_Renderer* renderer, SDL_Color* color) {
    int width = surface->w;
    int height = surface->h;

    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
    float offset = 0;

    if (Z >= 2) {
        offset = (Z-2) * 0.5f;
    }
    else {
        Z = 2;
    }

    // Define a rectangle
    SDL_FRect fillRect = { X - offset, Y - offset, Z, Z};

    // Fill the rectangle with the current drawing color
    SDL_RenderFillRect(renderer, &fillRect);
}

void Cell::SetPosition(float x, float y, float z) {
    // Call the original SetPosition from Position<float>
    Position::SetPosition(x, y, z);

    Z = mapNoiseToHeight(maxHeight, noise->GetNoise(X, Y));
}

// Function to map a value from -1..1 to 0..height
Uint8 Cell::mapNoiseToHeight(std::shared_ptr<Uint8> maxHeight, float noiseHeight) {
    return static_cast<Uint8>((noiseHeight + 1.0) * 0.5 * maxHeight.operator*());
}

Uint8 Cell::mapNoiseToColor(float height) {
    return static_cast<Uint8>((height + 1) * 0.5 * 255);
}