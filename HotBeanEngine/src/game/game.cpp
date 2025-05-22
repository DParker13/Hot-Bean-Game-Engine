/**
 * @file game.cpp
 * @author Daniel Parker (DParker13)
 * @brief Game base class. Registers default components.
 * @version 0.1
 * @date 2025-04-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "game.hpp"

namespace Core {
    namespace Application {
        Game::Game(const std::string& config_path)
            : Game(config_path, ComponentFactory()) {}

        Game::Game(const std::string& config_path, ComponentFactory component_factory)
            : App(config_path) {
            component_factory.RegisterComponents(*m_ecs_manager);
        }

        void Game::SetupSystems() {
            std::filesystem::path font_path = std::filesystem::current_path().parent_path() / "assets" / "fonts" / "LT_Superior_Mono" / "LTSuperiorMono-Regular.ttf";

            CameraSystem& camera_system = RegisterSystem<CameraSystem>();
            RegisterSystem<TransformSystem, CameraSystem&>(camera_system);
            RegisterSystem<PhysicsSystem>();
            RegisterSystem<RenderSystem>();
            RegisterSystem<InputSystem>();
            RegisterSystem<PlayerControllerSystem>();
            RegisterSystem<UISystem, std::string>(font_path.string());
            RegisterSystem<AudioSystem>();
        }
    }
}