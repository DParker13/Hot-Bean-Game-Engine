#include <SDL.h>
#include <SDL_main.h> // only include this one in the source file with main()!

#include "application/application.hpp"

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
int main(int argc, char* argv[]) {
    Application app("Ocean Simulator", SCREEN_WIDTH, SCREEN_HEIGHT);

    return 0;
}