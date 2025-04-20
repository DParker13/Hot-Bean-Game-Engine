#include <SDL_main.h> // only include this one in the source file with main()!

#include "game/test_game.hpp"

using namespace Core::Application;
using namespace Config;

/**
 * The main function of the program.
 *
 * @param argc the number of command line arguments
 * @param args an array of command line arguments
 *
 * @return an integer indicating the exit status of the program
 */
int main(int argc, char* argv[]) {
    TestGame game = TestGame(WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);

    game.Run();

    return 0;
}