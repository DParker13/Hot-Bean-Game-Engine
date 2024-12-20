#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include "FastNoiseLite.h"
#include "Entity.h"

class Cell : public Entity {
private:
    std::shared_ptr<FastNoiseLite> noise;
    std::unique_ptr<Position<float>> noisePos = std::make_unique<Position<float>>();
    std::shared_ptr<Uint8> maxHeight;

    void CreateRect(SDL_Surface* surface, SDL_Renderer* renderer, SDL_Color* color);
    Uint8 MapNoiseToHeight(std::shared_ptr<Uint8> maxHeight, float noiseHeight);
    Uint8 MapNoiseToColor(float height);

public:
    //Constructors
    Cell(std::shared_ptr<FastNoiseLite> noise, std::shared_ptr<Uint8> maxHeight);

    //Entity methods
    void OnInitialize() override;

    //InputSystem
    void OnUpdate(std::shared_ptr<float> deltaTime) override;
    void OnRender(SDL_Surface* surface, SDL_Renderer* renderer) override;

    void SetPosition(Position<float> newPos) override;
    void SetNoisePosition(float x, float y);

};