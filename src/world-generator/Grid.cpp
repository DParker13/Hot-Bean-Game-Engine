#include "Grid.h"

//Default Constructor that defines the width and height of this Grid
Grid::Grid(int width, int height)
	: Grid(width, height, std::make_shared<Uint8>(16), std::make_shared<Uint8>(16)) {
}

//Constructor that defines: width, height, grid spacing, and max height of grid cells
Grid::Grid(int width, int height, std::shared_ptr<Uint8> spacing, std::shared_ptr<Uint8> maxHeight)
	: width(width), height(height), spacing(spacing), maxHeight(maxHeight) {
	noise->SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	noise->SetSeed(0);

	// Initialize each cell
	for (int x = 0; x < width; x += *spacing) {
		for (int y = 0; y < height; y += *spacing) {
			std::unique_ptr<Cell> cell = std::make_unique<Cell>(noise, spacing, maxHeight);
			cell->UpdateLocalPosition(Position<float>((float)x, (float)y, 0.0f));

			cells.push_back(std::move(cell));
		}
	}
}

void Grid::OnInitialize() {
	// Initialize each cell
	for (int x = 0; x < width; x += *spacing) {
		for (int y = 0; y < height; y += *spacing) {
			cells.at(x)->SetParent(shared_from_this());
		}
	}
}

//EventSystem - Called every frame before OnRender
void Grid::OnUpdate() {
	for (int x = 0; x < cells.size(); ++x) {
		if (cells.at(x) != nullptr) {
			cells.at(x)->OnUpdate();
		}
		else {
			std::cout << "Attempted to call OnUpdate on Null Cell";
		}
	}
}

//EventSystem - Called every frame after all GameObjects states have been updated
void Grid::OnRender(SDL_Surface* surface, SDL_Renderer* renderer) {
	for (int z = 0; z < 16; z++) {
		for (int x = 0; x < cells.size(); ++x) {
			if (cells.at(x) != nullptr && cells.at(x)->GetPosition().Z == z) {
				cells.at(x)->OnRender(surface, renderer);
			}
		}
	}
}