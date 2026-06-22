/**
 * @file component_factory.cpp
 * @author Daniel Parker (DParker13)
 * @brief Default Component Factory Implementation
 * @version 0.1
 * @date 2025-07-06
 *
 * @copyright Copyright (c) 2025
 */

#include <HotBeanEngine/components/all_components.hpp>
#include <HotBeanEngine/components/component_factory.hpp>

namespace HBE::Components {
    using namespace Core;

    void ComponentFactory::RegisterComponents() {
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
     * @brief Adds a component to an entity from a component reader
     * @todo Create an expandable component creator for custom components.
     *
     * @param component_name Component Name
     * @param reader Component data reader
     * @param parent_entity Parent Entity
     * @param entity Entity
     */
    void ComponentFactory::CreateComponent(const std::string &component_name, ISerializationReader &reader,
                                           EntityID parent_entity, EntityID entity) {
        if (m_ecs_manager->IsComponentRegistered(component_name)) {
            if (component_name == "AudioSource") {
                AddComponent<AudioSource>(entity, reader);
            }
            else if (component_name == "Camera") {
                AddComponent<Camera>(entity, reader);
            }
            else if (component_name == "Collider2D") {
                AddComponent<Collider2D>(entity, reader);
            }
            else if (component_name == "Controller") {
                AddComponent<Controller>(entity, reader);
            }
            else if (component_name == "RigidBody") {
                AddComponent<RigidBody>(entity, reader);
            }
            else if (component_name == "Shape") {
                AddComponent<Shape>(entity, reader);
            }
            else if (component_name == "Text") {
                AddComponent<Text>(entity, reader);
            }
            else if (component_name == "Texture") {
                AddComponent<Texture>(entity, reader);
            }
            else if (component_name == "Interactive") {
                AddComponent<Interactive>(entity, reader);
            }
            else if (component_name == "Checkbox") {
                AddComponent<Checkbox>(entity, reader);
            }
            else if (component_name == "Slider") {
                AddComponent<Slider>(entity, reader);
            }
            else if (component_name == "Transform2D") {
                AddComponent<Transform2D, EntityID>(entity, reader, parent_entity);
            }
            else if (component_name == "UIRect") {
                AddComponent<UIRect>(entity, reader);
            }
            else if (component_name == "Shape") {
                AddComponent<Shape>(entity, reader);
            }
        }
        else {
            throw std::runtime_error("Component " + component_name +
                                     " is not registered. Cannot create component from serialized data provided.");
        }
    }
} // namespace HBE::Components