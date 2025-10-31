/**
 * @file default_component_factory.cpp
 * @author Daniel Parker (DParker13)
 * @brief Default Component Factory Implementation
 * @version 0.1
 * @date 2025-07-06
 * 
 * @copyright Copyright (c) 2025
 */

#include <HotBeanEngine/defaults/components/default_component_factory.hpp>

namespace HBE::Default::Components {
    void DefaultComponentFactory::RegisterComponents() {
        m_ecs_manager->RegisterComponentType<Components::AudioSource>();
        m_ecs_manager->RegisterComponentType<Components::Camera>();
        m_ecs_manager->RegisterComponentType<Components::Collider2D>();
        m_ecs_manager->RegisterComponentType<Components::Controller>();
        m_ecs_manager->RegisterComponentType<Components::RigidBody>();
        m_ecs_manager->RegisterComponentType<Components::Shape>();
        m_ecs_manager->RegisterComponentType<Components::Text>();
        m_ecs_manager->RegisterComponentType<Components::Texture>();
        m_ecs_manager->RegisterComponentType<Components::Transform2D>();
        m_ecs_manager->RegisterComponentType<Components::UIElement>();
    }

    /**
     * @brief Adds a component to an entity from a YAML node
     * @todo Create an expandable component creator for custom components.
     * 
     * @param component_name Component Name
     * @param node Component YAML Node
     * @param parent_entity Parent Entity
     * @param entity Entity
     */
    void DefaultComponentFactory::CreateComponentFromYAML(const std::string& component_name,
                                            YAML::Node node, Entity parent_entity, Entity entity) {
        if (m_ecs_manager->IsComponentRegistered(component_name)) {
            if (component_name == "AudioSource") {
                AddComponent<Components::AudioSource>(entity, node);
            }
            else if (component_name == "Camera") {
                AddComponent<Components::Camera>(entity, node);
            }
            else if (component_name == "Collider2D") {
                AddComponent<Components::Collider2D>(entity, node);
            }
            else if (component_name == "Controller") {
                AddComponent<Components::Controller>(entity, node);
            }
            else if (component_name == "RigidBody") {
                AddComponent<Components::RigidBody>(entity, node);
            }
            else if (component_name == "Shape") {
                AddComponent<Components::Shape>(entity, node);
            }
            else if (component_name == "Text") {
                AddComponent<Components::Text>(entity, node);
            }
            else if (component_name == "Texture") {
                AddComponent<Components::Texture>(entity, node);
            }
            else if (component_name == "Transform2D") {
                AddComponent<Components::Transform2D, Entity>(entity, node, parent_entity);
            }
            else if (component_name == "UIElement") {
                AddComponent<Components::UIElement>(entity, node);
            }
            else if (component_name == "Shape") {
                AddComponent<Components::Shape>(entity, node);
            }
        }
        else {
            throw std::runtime_error("Component " + component_name + " is not registered. Cannot create component from YAML file provided.");
        }
    }
}