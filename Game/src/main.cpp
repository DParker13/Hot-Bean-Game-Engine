#include <SDL3/SDL_main.h> // only include this one in the source file with main()!

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
    std::shared_ptr<IComponentFactory> component_factory = std::make_shared<DefaultComponentFactory>();
    
    ExampleGame game = ExampleGame(config_path, component_factory);
    game.Start();

    return 0;
}