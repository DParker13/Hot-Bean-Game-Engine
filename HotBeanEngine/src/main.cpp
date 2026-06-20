#include <SDL3/SDL_main.h> // only include this one in the source file with main()!

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/components/component_factory.hpp>

/**
 * The main function of the program.
 *
 * @param argc the number of command line arguments
 * @param args an array of command line arguments
 *
 * @return an integer indicating the exit status of the program
 */
int main(int argc, char *argv[]) {
    std::shared_ptr<HBE::Application::IComponentFactory> component_factory =
        std::make_shared<HBE::Components::ComponentFactory>();

    HBE::Application::Application app = HBE::Application::Application(component_factory);
    app.Start();

    return 0;
}