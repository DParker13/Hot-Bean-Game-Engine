#ifndef CELL_H
#define CELL_H

#include <memory>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_render.h>
#include "FastNoiseLite.h"
#include "GameObject.h"

class Cell : public GameObject {
private:
    std::shared_ptr<Uint8> spacing;
    std::shared_ptr<Uint8> maxHeight;
    std::shared_ptr<FastNoiseLite> noise;

    // Function to set a pixel on an SDL_Surface
    void createRect(SDL_Surface* surface, SDL_Renderer* renderer, SDL_Color* color);
    Uint8 mapNoiseToHeight(std::shared_ptr<Uint8> maxHeight, float noiseHeight);
    Uint8 mapNoiseToColor(float height);

public:
    Cell(std::shared_ptr<FastNoiseLite> noise, std::shared_ptr<Uint8> spacing, std::shared_ptr<Uint8> maxHeight);

    void OnUpdate() override;
    void OnRender(SDL_Surface* surface, SDL_Renderer* renderer) override;

    void SetPosition(float x, float y, float z) override;

};
#endif // CELL_H