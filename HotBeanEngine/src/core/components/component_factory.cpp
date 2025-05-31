#include "component_factory.hpp"

namespace Core::Application {

    void ComponentFactory::RegisterComponents(Core::Managers::ECSManager& ecs_manager) {
        ecs_manager.RegisterComponentType<Components::AudioSource>();
        ecs_manager.RegisterComponentType<Components::Camera>();
        ecs_manager.RegisterComponentType<Components::Collider2D>();
        ecs_manager.RegisterComponentType<Components::Controller>();
        ecs_manager.RegisterComponentType<Components::RigidBody>();
        ecs_manager.RegisterComponentType<Components::Text>();
        ecs_manager.RegisterComponentType<Components::Texture>();
        ecs_manager.RegisterComponentType<Components::Tile>();
        ecs_manager.RegisterComponentType<Components::Transform2D>();
        ecs_manager.RegisterComponentType<Components::UIElement>();
    }

    /**
     * @brief Adds a component to an entity from a YAML node
     * @todo Create an expandable component creator for custom components.
     * 
     * @param ecs_manager ECS Manager
     * @param component_name Component Name
     * @param node Component YAML Node
     * @param entity Entity
     */
    void ComponentFactory::CreateComponent(Core::Managers::ECSManager& ecs_manager, const std::string& component_name,
                                            YAML::Node node, Entity parent_entity, Entity entity) {
        if (ecs_manager.IsComponentRegistered(component_name)) {
            if (component_name == "AudioSource") {
                AddComponent<Components::AudioSource>(ecs_manager, entity, node);
            }
            else if (component_name == "Camera") {
                AddComponent<Components::Camera>(ecs_manager, entity, node);
            }
            else if (component_name == "Collider2D") {
                AddComponent<Components::Collider2D>(ecs_manager, entity, node);
            }
            else if (component_name == "Controller") {
                AddComponent<Components::Controller>(ecs_manager, entity, node);
            }
            else if (component_name == "RigidBody") {
                AddComponent<Components::RigidBody>(ecs_manager, entity, node);
            }
            else if (component_name == "Text") {
                AddComponent<Components::Text>(ecs_manager, entity, node);
            }
            else if (component_name == "Texture") {
                AddComponent<Components::Texture>(ecs_manager, entity, node);
            }
            else if (component_name == "Tile") {
                AddComponent<Components::Tile>(ecs_manager, entity, node);
            }
            else if (component_name == "Transform2D") {
                AddComponent<Components::Transform2D>(ecs_manager, entity, node);
                ecs_manager.GetComponent<Components::Transform2D>(entity).m_parent = parent_entity;
            }
            else if (component_name == "UIElement") {
                AddComponent<Components::UIElement>(ecs_manager, entity, node);
            }
        }
        else {
            throw std::runtime_error("Component " + component_name + " is not registered. Cannot create component from YAML file provided.");
        }
    }
}