#include <SDL.h>
#include <SDL_main.h> // only include this one in the source file with main()!

#include "application/game.hpp"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

/**
 * The main function of the program.
 *
 * @param argc the number of command line arguments
 * @param args an array of command line arguments
 *
 * @return an integer indicating the exit status of the program
 */
int main(int argc, char* argv[]) {
    Application::Game game = Application::Game("Hot Bean Engine", SCREEN_WIDTH, SCREEN_HEIGHT);

    game.Run();

    return 0;
}