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
        m_ecs_manager->RegisterComponentID<AudioSource>();
        m_ecs_manager->RegisterComponentID<Camera>();
        m_ecs_manager->RegisterComponentID<Collider2D>();
        m_ecs_manager->RegisterComponentID<Controller>();
        m_ecs_manager->RegisterComponentID<RigidBody>();
        m_ecs_manager->RegisterComponentID<Shape>();
        m_ecs_manager->RegisterComponentID<Interactive>();
        m_ecs_manager->RegisterComponentID<Checkbox>();
        m_ecs_manager->RegisterComponentID<Slider>();
        m_ecs_manager->RegisterComponentID<Text>();
        m_ecs_manager->RegisterComponentID<Texture>();
        m_ecs_manager->RegisterComponentID<Transform2D>();
        m_ecs_manager->RegisterComponentID<UIRect>();
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
    void DefaultComponentFactory::CreateComponentFromYAML(const std::string &component_name, YAML::Node node,
                                                          EntityID parent_entity, EntityID entity) {
        if (m_ecs_manager->IsComponentRegistered(component_name)) {
            if (component_name == "AudioSource") {
                AddComponent<AudioSource>(entity, node);
            }
            else if (component_name == "Camera") {
                AddComponent<Camera>(entity, node);
            }
            else if (component_name == "Collider2D") {
                AddComponent<Collider2D>(entity, node);
            }
            else if (component_name == "Controller") {
                AddComponent<Controller>(entity, node);
            }
            else if (component_name == "RigidBody") {
                AddComponent<RigidBody>(entity, node);
            }
            else if (component_name == "Shape") {
                AddComponent<Shape>(entity, node);
            }
            else if (component_name == "Text") {
                AddComponent<Text>(entity, node);
            }
            else if (component_name == "Texture") {
                AddComponent<Texture>(entity, node);
            }
            else if (component_name == "Interactive") {
                AddComponent<Interactive>(entity, node);
            }
            else if (component_name == "Checkbox") {
                AddComponent<Checkbox>(entity, node);
            }
            else if (component_name == "Slider") {
                AddComponent<Slider>(entity, node);
            }
            else if (component_name == "Transform2D") {
                AddComponent<Transform2D, EntityID>(entity, node, parent_entity);
            }
            else if (component_name == "UIRect") {
                AddComponent<UIRect>(entity, node);
            }
            else if (component_name == "Shape") {
                AddComponent<Shape>(entity, node);
            }
        }
        else {
            throw std::runtime_error("Component " + component_name +
                                     " is not registered. Cannot create component from YAML file provided.");
        }
    }
} // namespace HBE::Default::Components