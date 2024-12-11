#include <SDL.h>
#include <SDL_main.h> // only include this one in the source file with main()!
#include <iostream>
#include "Application.h"

#include "core/ecs.hpp"
#include "core/core_manager.hpp"
#include "components/transform.hpp"
#include "components/gravity.hpp"
#include "systems/physics_system.hpp"
#include "systems/render_system.hpp"
#include "systems/input_system.hpp"

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
int main(int argc, char* args[]) {
    Application app("Ocean Simulator", SCREEN_WIDTH, SCREEN_HEIGHT);
    
    Core::CoreManager coreManager;
    coreManager.Init();
    Entity firstEnt = coreManager.CreateEntity();

    // Add the components
    Components::Transform transform = Components::Transform();
    Components::Gravity gravity = Components::Gravity();
    Components::RigidBody rigidBody = Components::RigidBody();

    // Register the systems
    auto physicsSystem = coreManager.RegisterSystem<Systems::PhysicsSystem>();
    auto renderSystem = coreManager.RegisterSystem<Systems::RenderSystem>();
    auto inputSystem = coreManager.RegisterSystem<Systems::InputSystem>();

    Signature signature;
    signature.set(coreManager.RegisterComponentType<Components::Transform>());
    signature.set(coreManager.RegisterComponentType<Components::Gravity>());
    signature.set(coreManager.RegisterComponentType<Components::RigidBody>());
    coreManager.SetSignature<Systems::PhysicsSystem>(signature);

    signature.reset();
    signature.set(coreManager.GetComponentType<Components::Transform>());
    coreManager.SetSignature<Systems::RenderSystem>(signature);

    signature.reset();
    signature.set(coreManager.GetComponentType<Components::Transform>());
    coreManager.SetSignature<Systems::InputSystem>(signature);

    coreManager.AddComponent<Components::Transform>(firstEnt, transform);
    coreManager.AddComponent<Components::Gravity>(firstEnt, gravity);
    //coreManager.AddComponent<Components::RigidBody>(firstEnt, rigidBody);

    //coreManager.Print();

    app.Run(coreManager);

    return 0;
}