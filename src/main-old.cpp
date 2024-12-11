#include <SDL.h>
#include <SDL_main.h> // only include this one in the source file with main()!
#include <iostream>
#include "Grid.h"
#include "Text.h"
#include "Controller.h"
#include "Application.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

/**
 * The main function of the program.
 *
 * @param argc the number of command line arguments
 * @param args an array of command line arguments
 *
 * @return an integer indicating the exit status of the program
 *
 * @throws None
 */
int main(int argc, char* args[]) {
    Application app("Ocean Simulator", SCREEN_WIDTH, SCREEN_HEIGHT);

    std::shared_ptr<Grid> grid = std::make_shared<Grid>(SCREEN_WIDTH, SCREEN_HEIGHT, 16, 40);
    std::shared_ptr<Controller> playerController = std::make_shared<Controller>(100.0f, grid);
    app.AddObject(playerController);
    app.AddObject(std::make_shared<Text>("Hello, World!"));

    app.Run();

    return 0;
}