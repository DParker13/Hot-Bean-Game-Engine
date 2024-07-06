#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include "FastNoiseLite.h"
#include "GameObject.h"

class Cell : public GameObject {
private:
    std::unique_ptr<Position<float>> noisePos = std::make_unique<Position<float>>();
    std::shared_ptr<Uint8> spacing;
    std::shared_ptr<Uint8> maxHeight;
    std::shared_ptr<FastNoiseLite> noise;

    void CreateRect(SDL_Surface* surface, SDL_Renderer* renderer, SDL_Color* color);
    Uint8 MapNoiseToHeight(std::shared_ptr<Uint8> maxHeight, float noiseHeight);
    Uint8 MapNoiseToColor(float height);

public:
    //Constructors
    Cell(std::shared_ptr<FastNoiseLite> noise, std::shared_ptr<Uint8> spacing, std::shared_ptr<Uint8> maxHeight);

    //EventSystem
    void OnUpdate() override;
    void OnRender(SDL_Surface* surface, SDL_Renderer* renderer) override;

    void UpdateLocalPosition(Position<float> newPos) override;
    void SetNoisePosition(float x, float y);

};