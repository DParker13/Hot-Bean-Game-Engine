#include <SDL3/SDL_main.h> // only include this one in the source file with main()!

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/components/component_factory.hpp>
#include <HotBeanEngine/systems/system_factory.hpp>

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

    std::shared_ptr<HBE::Application::ISystemFactory> system_factory =
        std::make_shared<HBE::Application::SystemFactory>();

    HBE::Application::Application app = HBE::Application::Application(component_factory, system_factory);
    app.Start();

    return 0;
}