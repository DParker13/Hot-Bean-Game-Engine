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
    std::string config_path = "C:\\Users\\danie\\Documents\\GitHub\\HotBeanEngine\\Game\\src\\config.yaml";
    
    TestGame game = TestGame(config_path);

    game.Run();

    return 0;
}