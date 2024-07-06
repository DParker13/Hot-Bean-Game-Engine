#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h> // only include this one in the source file with main()!
#include <iostream>
#include "Grid.h"
#include "Application.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main(int argc, char* args[]) {
    Application app("Ocean Simulator", SCREEN_WIDTH, SCREEN_HEIGHT);

    std::shared_ptr<Grid> grid = std::make_shared<Grid>(SCREEN_WIDTH, SCREEN_HEIGHT);
    grid->OnInitialize();
    app.AddObject(grid);

    app.Run();

    return 0;
}