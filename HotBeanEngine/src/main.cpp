#include <SDL3/SDL_main.h> // only include this one in the source file with main()!

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/factories/component_factory.hpp>
#include <HotBeanEngine/factories/scene_factory.hpp>
#include <HotBeanEngine/factories/system_factory.hpp>

/**
 * The main function of the program.
 *
 * @param argc the number of command line arguments
 * @param args an array of command line arguments
 *
 * @return an integer indicating the exit status of the program
 */
int main(int argc, char *argv[]) {
    std::shared_ptr<HBE::Factories::IComponentFactory> component_factory =
        std::make_shared<HBE::Factories::ComponentFactory>();

    std::shared_ptr<HBE::Factories::ISystemFactory> system_factory = std::make_shared<HBE::Factories::SystemFactory>();
    std::shared_ptr<HBE::Factories::ISceneFactory> scene_factory = std::make_shared<HBE::Factories::SceneFactory>();

    HBE::Application::Application app = HBE::Application::Application(component_factory, system_factory, scene_factory);
    app.Start();

    return 0;
}