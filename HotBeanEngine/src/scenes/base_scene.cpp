#include "base_scene.hpp"

namespace HBE::Application {
     /**
      * @brief Initializes the default systems needed for basic game functionality.
      * The order each system is initialized is important! That is the order they are then called.
      */
    void BaseScene::SetupSystems() {
        std::filesystem::path font_path = std::filesystem::current_path() / "assets" / "fonts" / "LT_Superior_Mono" / "LTSuperiorMono-Regular.ttf";

        // Input
        InputSystem& input_system = RegisterSystem<InputSystem>();
        RegisterSystem<PlayerControllerSystem, InputSystem&>(input_system);

        // Transform
        CameraSystem& camera_system = RegisterSystem<CameraSystem>();
        RegisterSystem<TransformSystem, CameraSystem&>(camera_system);
        RegisterSystem<CollisionSystem, int>(5);

        // Physics
        RegisterSystem<PhysicsSystem, InputSystem&>(input_system);
        RegisterSystem<AudioSystem>();

        // Rendering
        RegisterSystem<ShapeSystem>();
        RegisterSystem<UISystem, std::string>(font_path.string());
        RegisterSystem<RenderSystem, InputSystem&>(input_system);
    };
}