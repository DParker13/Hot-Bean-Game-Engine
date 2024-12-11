#include "Grid.h"

//Default Constructor that defines the width and height of this Grid
Grid::Grid(Uint16 width, Uint16 height)
	: Grid(width, height, Position<float>(0.0f, 0.0f, 0.0f)) {
}

//Constructor that defines the width, height, and starting position of this Grid
Grid::Grid(Uint16 width, Uint16 height, Uint8 spacing, Uint8 maxHeight)
	: Grid(width, height, Position<float>(), spacing, maxHeight) {
}

//Constructor that defines the width, height, and starting position of this Grid
Grid::Grid(Uint16 width, Uint16 height, Position<float> startingPos)
	: Grid(width, height, startingPos, 16, 16) {
}

//Constructor that defines: width, height, grid spacing, and max height of grid cells
Grid::Grid(Uint16 width, Uint16 height, Position<float> startingPos, Uint8 spacing, Uint8 maxHeight)
	: Entity(startingPos), width(width), height(height), spacing(spacing), maxHeight(maxHeight) {

	// Initialize each cell
	for (int x = 0; x < width; x += spacing) {
		for (int y = 0; y < height; y += spacing) {
			std::shared_ptr<Cell> cell = std::make_shared<Cell>(noise, std::make_shared<Uint8>(maxHeight));
			cell->SetPosition(Position<float>((float)x, (float)y, 0.0f));

			cells.push_back(std::move(cell));
		}
	}
}

void Grid::OnInitialize() {
	noise->SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	noise->SetSeed(0);

	for(auto& cell : cells) {
		AddChild(cell);
	}

	Entity::OnInitialize();
}