#include <SDL3/SDL_main.h> // only include this one in the source file with main()!

#include "game/example_game.hpp"
#include <HotBeanEngine/editor/editor_gui.hpp>
#include <HotBeanEngine/defaults/components/default_component_factory.hpp>

/**
 * The main function of the program.
 *
 * @param argc the number of command line arguments
 * @param args an array of command line arguments
 *
 * @return an integer indicating the exit status of the program
 */
int main(int argc, char *argv[]) {
    std::string config_path = (std::filesystem::current_path().parent_path() / "Game" / "assets" / "config.yaml").string();
    std::shared_ptr<HBE::Application::IComponentFactory> component_factory =
        std::make_shared<HBE::Default::Components::DefaultComponentFactory>();

    std::unique_ptr<HBE::Application::GUI::IEditorGUI> editor_gui =
        std::make_unique<HBE::Application::GUI::EditorGUI>();

    Game::ExampleGame game = Game::ExampleGame(config_path, component_factory, std::move(editor_gui));
    game.Start();

    return 0;
}