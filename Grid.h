#ifndef GRID_H
#define GRID_H

#include "GameObject.h"
#include "Cell.h"
#include "Matrix.h"
#include "FastNoiseLite.h"

class Grid : public GameObject {
private:
    std::shared_ptr<Uint8> spacing;
    std::shared_ptr<Uint8> maxHeight;
    std::shared_ptr<FastNoiseLite> noise = std::make_shared<FastNoiseLite>();
    std::vector<std::unique_ptr<Cell>> cells;

public:
    Grid(int width, int height, std::shared_ptr<Uint8> spacing, std::shared_ptr<Uint8> maxHeight);
    Grid(int width, int height);

    void OnUpdate() override;
    void OnRender(SDL_Surface* surface, SDL_Renderer* renderer) override;

};
#endif // GRID_H