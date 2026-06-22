#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/factories/system_factory.hpp>
#include <HotBeanEngine/systems/all_systems.hpp>

namespace HBE::Factories {
    using namespace Systems;

    void SystemFactory::RegisterSystems() {
        std::filesystem::path font_path = std::filesystem::current_path().parent_path() / "assets" / "fonts" /
                                          "LT_Superior_Mono" / "LTSuperiorMono-Regular.ttf";

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
} // namespace HBE::Factories