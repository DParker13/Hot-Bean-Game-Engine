/**
 * @file scene.cpp
 * @author Daniel Parker (DParker13)
 * @brief Default scene implementation. Sets up default systems for a basic game scene.
 * @version 0.1
 * @date 2025-12-24
 *
 * @copyright Copyright (c) 2025
 */

#include <HotBeanEngine/application/scene.hpp>
#include <HotBeanEngine/systems/all_systems.hpp>

namespace HBE::Application {
    using namespace Application;
    using namespace Systems;

    void Scene::SetupSystems() {
        if (IncludeDefaultSystems()) {
            SetupDefaultSystems();
        }

        SetupCustomSystems();
    }

    void Scene::SetupScene() {
        // Any scene-specific setup can be done here
    }

    void Scene::SetupDefaultSystems() {
        std::filesystem::path font_path =
            std::filesystem::current_path() / "assets" / "fonts" / "LT_Superior_Mono" / "LTSuperiorMono-Regular.ttf";

        // Input
        g_ecs.RegisterSystem<PlayerControllerSystem>();

        // Physics
        g_ecs.RegisterSystem<PhysicsSystem>();
        g_ecs.RegisterSystem<CollisionSystem>();

        // Rendering
        g_ecs.RegisterSystem<ShapeSystem>();
        g_ecs.RegisterSystem<TextSystem, std::string>(font_path.string());
        g_ecs.RegisterSystem<InteractSystem>();
    }
} // namespace HBE::Application