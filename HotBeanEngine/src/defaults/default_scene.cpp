/**
 * @file default_scene.cpp
 * @author Daniel Parker (DParker13)
 * @brief Default scene implementation. Sets up default systems for a basic game scene.
 * @version 0.1
 * @date 2025-12-24
 *
 * @copyright Copyright (c) 2025
 */

#include <HotBeanEngine/defaults/default_scene.hpp>
#include <HotBeanEngine/defaults/systems/default_systems.hpp>

namespace HBE::Default {
    using namespace HBE::Application;
    using namespace HBE::Default::Systems;

    void DefaultScene::SetupSystems() {
        std::filesystem::path font_path =
            std::filesystem::current_path() / "assets" / "fonts" / "LT_Superior_Mono" / "LTSuperiorMono-Regular.ttf";

        // Input
        g_ecs.RegisterSystem<PlayerControllerSystem>();

        // Physics
        g_ecs.RegisterSystem<PhysicsSystem>();
        g_ecs.RegisterSystem<CollisionSystem>();

        // Rendering
        g_ecs.RegisterSystem<ShapeSystem>();
        g_ecs.RegisterSystem<UISystem, std::string>(font_path.string());
    };
} // namespace HBE::Default