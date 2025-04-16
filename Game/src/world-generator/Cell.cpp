#include "Cell.hpp"

Cell::Cell(std::shared_ptr<FastNoiseLite> noise, std::shared_ptr<Uint8> maxHeight)
    : noise(noise), maxHeight(maxHeight) {
}

void Cell::OnInitialize() {
    Entity::OnInitialize();

    SetNoisePosition(GetPosition().X, GetPosition().Y);
}

void Cell::OnUpdate(std::shared_ptr<float> deltaTime) {
    SetNoisePosition(GetPosition().X, GetPosition().Y);
}

void Cell::OnRender(SDL_Surface* surface, SDL_Renderer* renderer) {
    //Calling base OnRender
    Entity::OnRender(surface, renderer);

    Uint8 colorVal = MapNoiseToColor(noise->GetNoise(noisePos->X, noisePos->Y));
    SDL_Color color = { colorVal, colorVal, colorVal, 0xFF };

    CreateRect(surface, renderer, &color);
}

// Function to fill a rectangle on an SDL_Surface
void Cell::CreateRect(SDL_Surface* surface, SDL_Renderer* renderer, SDL_Color* color) {
    int width = surface->w;
    int height = surface->h;

    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
    float offset = 0;
    float z = noisePos->Z;

    if (z >= 2) {
        offset = (z-2) * 0.5f;
    }
    else {
        z = 2;
    }

    // Define a rectangle
    SDL_FRect fillRect = { GetPosition().X - offset, GetPosition().Y - offset, z, z};

    // Fill the rectangle with the current drawing color
    SDL_RenderFillRectF(renderer, &fillRect);
}

void Cell::SetPosition(Position<float> newPos) {
    //Update this Cell's position
    Entity::SetPosition(newPos);

    //Update this Cell's noise position
    SetNoisePosition(newPos.X, newPos.Y);
}

void Cell::SetNoisePosition(float x, float y) {
    noisePos->SetPosition(x, y, MapNoiseToHeight(maxHeight, noise->GetNoise(x, y)));
}

// Function to map a value from -1..1 to 0..height
Uint8 Cell::MapNoiseToHeight(std::shared_ptr<Uint8> maxHeight, float noiseHeight) {
    return static_cast<Uint8>((noiseHeight + 1.0) * 0.5 * *maxHeight);
}

Uint8 Cell::MapNoiseToColor(float height) {
    return static_cast<Uint8>((height + 1) * 0.5 * 255);
}