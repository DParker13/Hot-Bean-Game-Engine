#include "Grid.h"
#include <iostream>

Grid::Grid(int width, int height, std::shared_ptr<Uint8> spacing, std::shared_ptr<Uint8> maxHeight) {
	noise->SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	noise->SetSeed(0);

	// Initialize each cell
	for (int x = 0; x < width; x += 16) {
		for (int y = 0; y < height; y += 16) {
			std::unique_ptr<Cell> cell = std::make_unique<Cell>(noise, spacing, maxHeight);
			cell->SetPosition((float)x, (float)y, 0);

			cells.push_back(std::move(cell));
		}
	}
}

Grid::Grid(int width, int height)
	: Grid(width, height, std::make_shared<Uint8>(16), std::make_shared<Uint8>(16)) {

}

void Grid::OnUpdate() {
	for (int x = 0; x < cells.size(); ++x) {
		if (cells.at(x) != nullptr) {
			cells.at(x)->OnUpdate();
		}
	}
}

void Grid::OnRender(SDL_Surface* surface, SDL_Renderer* renderer) {
	for (int z = 0; z < 16; z++) {
		for (int x = 0; x < cells.size(); ++x) {
			if (cells.at(x) != nullptr && cells.at(x)->Z == z) {
				cells.at(x)->OnRender(surface, renderer);
			}
		}
	}
}