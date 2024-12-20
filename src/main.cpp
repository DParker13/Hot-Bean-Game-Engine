#include <SDL.h>
#include <SDL_main.h> // only include this one in the source file with main()!
#include <iostream>

#include "application/application.hpp"
#include "managers/core_manager.hpp"
#include "systems/physics_system.hpp"
#include "systems/render_system.hpp"
#include "systems/input_system.hpp"
#include "systems/player_controller_system.hpp"

#include "gameobjects/text.hpp"
#include "gameobjects/player.hpp"

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

    return 0;
}