#include "base_scene.hpp"

namespace Core::Application {
     /**
      * @brief Initializes the default systems needed for basic game functionality.
      * The order each system is initialized is important! That is the order they are then called.
      */
    void BaseScene::SetupSystems() {
        std::filesystem::path font_path = std::filesystem::current_path() / "assets" / "fonts" / "LT_Superior_Mono" / "LTSuperiorMono-Regular.ttf";

        InputSystem& input_system = RegisterSystem<InputSystem>();
        RegisterSystem<PlayerControllerSystem, InputSystem&>(input_system);
        RegisterSystem<PhysicsSystem>();
        RegisterSystem<UISystem, std::string>(font_path.string());
        RegisterSystem<AudioSystem>();

        CameraSystem& camera_system = RegisterSystem<CameraSystem>();
        RegisterSystem<TransformSystem, CameraSystem&>(camera_system);

        // Should be last to have the most up to date components
        RegisterSystem<RenderSystem>();
    };
}