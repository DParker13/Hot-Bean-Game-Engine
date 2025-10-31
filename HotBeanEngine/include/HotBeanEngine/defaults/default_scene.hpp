/**
 * @file default_scene.hpp
 * @author Daniel Parker (DParker13)
 * @brief Default scene implementation. Sets up default systems for a basic game scene.
 * @version 0.1
 * @date 2025-10-17
 * 
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/defaults/systems/default_systems.hpp>
#include <HotBeanEngine/defaults/default_scene_serializer.hpp>

using namespace HBE::Default::Systems;
using namespace HBE::Default::Components;

namespace HBE::Default {
    /**
     * @brief Default scene implementation with standard setup
     * 
     * Provides basic scene configuration and system initialization.
     * Serves as template for custom scene implementations.
     */
    class DefaultScene : public Scene {
    public:
        DefaultScene(std::string name, std::string path, std::shared_ptr<ISerializer> serializer)
            : Scene(name, path, serializer) {}

        /**
         * @brief Initializes the default systems needed for basic game functionality.
         * The order each system is initialized is important! That is the order they are then called.
         */
        void SetupSystems() {
            std::filesystem::path font_path = std::filesystem::current_path() / "assets" / "fonts" / "LT_Superior_Mono" / "LTSuperiorMono-Regular.ttf";

            // Input
            InputSystem& input_system = g_ecs.RegisterSystem<InputSystem>();
            g_ecs.RegisterSystem<PlayerControllerSystem, InputSystem&>(input_system);
            g_ecs.RegisterSystem<AudioSystem>();

            // Physics
            g_ecs.RegisterSystem<PhysicsSystem, InputSystem&>(input_system);
            g_ecs.RegisterSystem<CollisionSystem>();

            // Transform and Camera
            g_ecs.RegisterSystem<TransformSystem>();
            CameraSystem& camera_system = g_ecs.RegisterSystem<CameraSystem>();

            // Rendering
            g_ecs.RegisterSystem<ShapeSystem, CameraSystem&>(camera_system);
            g_ecs.RegisterSystem<UISystem, std::string>(font_path.string());
            g_ecs.RegisterSystem<RenderSystem, InputSystem&, CameraSystem&>(input_system, camera_system);
        };
    };
}