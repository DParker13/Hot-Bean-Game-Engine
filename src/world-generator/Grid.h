#pragma once

#include <iostream>
#include "Entity.h"
#include "Matrix.h"
#include "Cell.h"

class Grid : public Entity {
private:
    Uint16 width;
    Uint16 height;
    Uint8 spacing;
    Uint8 maxHeight;
    std::shared_ptr<FastNoiseLite> noise = std::make_shared<FastNoiseLite>();
    std::vector<std::shared_ptr<Cell>> cells;

public:
    Grid(Uint16 width, Uint16 height);
    Grid(Uint16 width, Uint16 height, Uint8 spacing, Uint8 maxHeight);
    Grid(Uint16 width, Uint16 height, Position<float> startingPos);
    Grid(Uint16 width, Uint16 height, Position<float> startingPos, Uint8 spacing, Uint8 maxHeight);

    //Entity methods
    void OnInitialize() override;
};