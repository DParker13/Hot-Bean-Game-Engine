#include "component_register.hpp"

namespace Core::Managers::Helpers {
    void ComponentRegister::RegisterComponents() {
        std::shared_ptr<ECSManager> ecsManager = App::GetInstance().GetECSManager();

        ecsManager->RegisterComponentType<AudioSource>();
        ecsManager->RegisterComponentType<Collider2D>();
        ecsManager->RegisterComponentType<Controller>();
        ecsManager->RegisterComponentType<RigidBody>();
        ecsManager->RegisterComponentType<Text>();
        ecsManager->RegisterComponentType<Texture>();
        ecsManager->RegisterComponentType<Tile>();
        ecsManager->RegisterComponentType<Transform2D>();
        ecsManager->RegisterComponentType<UIElement>();
    }

    void ComponentRegister::CreateComponent(ECSManager& ecs_manager, const std::string& component_name,
                                            YAML::Node node, Entity entity) {
        if (ecs_manager.IsComponentRegistered(component_name)) {
            if (component_name == "Transform2D") {
                AddComponent<Transform2D>(ecs_manager, entity, node);
            }
            else if (component_name == "Texture") {
                AddComponent<Texture>(ecs_manager, entity, node);
            }
            else if (component_name == "Collider2D") {
                AddComponent<Collider2D>(ecs_manager, entity, node);
            }
            else if (component_name == "RigidBody") {
                AddComponent<RigidBody>(ecs_manager, entity, node);
            }
            else if (component_name == "AudioSource") {
                AddComponent<AudioSource>(ecs_manager, entity, node);
            }
            else if (component_name == "Text") {
                AddComponent<Text>(ecs_manager, entity, node);
            }
            else if (component_name == "Tile") {
                AddComponent<Tile>(ecs_manager, entity, node);
            }
            else if (component_name == "Controller") {
                AddComponent<Controller>(ecs_manager, entity, node);
            }
            else if (component_name == "UIElement") {
                AddComponent<UIElement>(ecs_manager, entity, node);
            }
        }
        else {
            throw std::runtime_error("Component " + component_name + " is not registered. Cannot create component from YAML file provided.");
        }
    }
}