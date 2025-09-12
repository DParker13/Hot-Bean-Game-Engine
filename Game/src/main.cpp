#include <SDL_main.h> // only include this one in the source file with main()!

#include "game/example_game.hpp"

/**
 * The main function of the program.
 *
 * @param argc the number of command line arguments
 * @param args an array of command line arguments
 *
 * @return an integer indicating the exit status of the program
 */
int main(int argc, char* argv[]) {
    std::string config_path = (std::filesystem::current_path() / "config.yaml").string();
    
    ExampleGame game = ExampleGame(config_path);
    game.Start();

    return 0;
}