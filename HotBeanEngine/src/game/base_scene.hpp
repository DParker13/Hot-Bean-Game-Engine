#pragma once

#include "base_game.hpp"
#include "../archetypes/default_archetypes.hpp"

using namespace Core::Systems;

namespace Core::Application {
    class BaseScene : public Scene {
        public:
            BaseScene(std::string name, std::string scene_path) : Scene(name, scene_path) {}

            /**
             * @brief Initializes the default systems needed for basic game functionality.
             */
            void SetupPreSystems() override {
                std::filesystem::path font_path = std::filesystem::current_path() / "assets" / "fonts" / "LT_Superior_Mono" / "LTSuperiorMono-Regular.ttf";

                RegisterSystem<InputSystem>();
                RegisterSystem<PlayerControllerSystem>();
                RegisterSystem<PhysicsSystem>();
                RegisterSystem<UISystem, std::string>(font_path.string());
                RegisterSystem<AudioSystem>();
            };

            /**
             * @brief Initializes the default systems needed for basic game functionality.
             */
            void SetupPostSystems() override {
                CameraSystem& camera_system = RegisterSystem<CameraSystem>();
                RegisterSystem<TransformSystem, CameraSystem&>(camera_system);
                RegisterSystem<RenderSystem>();
            }

        protected:
            template <typename System, typename... Args>
            System& RegisterSystem(Args&&... args) {
                return App::GetInstance().GetECSManager()->RegisterSystem<System, Args&&...>(std::forward<Args>(args)...);
            }
    };
}