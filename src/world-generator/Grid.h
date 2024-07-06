#pragma once

#include <iostream>
#include "GameObject.h"
#include "Matrix.h"
#include "Cell.h"

class Grid : public GameObject {
private:
    int width;
    int height;
    std::shared_ptr<Uint8> spacing;
    std::shared_ptr<Uint8> maxHeight;
    std::shared_ptr<FastNoiseLite> noise = std::make_shared<FastNoiseLite>();
    std::vector<std::unique_ptr<Cell>> cells;

public:
    Grid(int width, int height);
    Grid(int width, int height, std::shared_ptr<Uint8> spacing, std::shared_ptr<Uint8> maxHeight);

    void OnInitialize();
    void OnUpdate() override;
    void OnRender(SDL_Surface* surface, SDL_Renderer* renderer) override;

};