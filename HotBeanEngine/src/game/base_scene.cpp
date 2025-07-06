#include "base_scene.hpp"

namespace Core::Application {
    /**
     * @brief Initializes the default systems needed for basic game functionality.
     */
    void BaseScene::SetupPreSystems() {
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
    void BaseScene::SetupPostSystems() {
        CameraSystem& camera_system = RegisterSystem<CameraSystem>();
        RegisterSystem<TransformSystem, CameraSystem&>(camera_system);
        RegisterSystem<RenderSystem>();
    }
}