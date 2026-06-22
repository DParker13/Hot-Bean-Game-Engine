/**
 * @file yaml_scene_serializer.cpp
 * @author Daniel Parker (DParker13)
 * @brief YAML-backed implementation of the ISerializer interface.
 * @version 1.0
 * @date 2025-10-11
 *
 * @copyright Copyright (c) 2025
 */

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/components/miscellaneous/transform_2d.hpp>
#include <HotBeanEngine/serializers/yaml/yaml_scene_serializer.hpp>
#include <HotBeanEngine/serializers/yaml/yaml_serialization_reader.hpp>
#include <HotBeanEngine/serializers/yaml/yaml_serialization_writer.hpp>

namespace HBE::Serializers {
    using namespace Core;
    using namespace Components;

    void YamlSceneSerializer::Serialize(std::filesystem::path filepath) {
        assert(!filepath.empty() && "Current filepath is empty.");

        YAML::Emitter out = YAML::Emitter();

        MapParentEntities();

        out << YAML::BeginMap;
        SerializeEntities(out, -1);
        out << YAML::EndMap;

        std::ofstream file{filepath};
        file << out.c_str();
    }

    // TODO: Replace this with a better solution. Maybe use the TransformSystem.m_entities member instead
    void YamlSceneSerializer::MapParentEntities() {
        for (EntityID entity = 0; entity < g_ecs.EntityCount(); entity++) {
            if (g_ecs.HasComponent<Transform2D>(entity)) {
                EntityID parent_entity = g_ecs.GetComponent<Transform2D>(entity).m_parent;

                if (m_parent_entity_map.find(parent_entity) == m_parent_entity_map.end()) {
                    m_parent_entity_map[parent_entity] = std::vector<EntityID>{entity};
                }
                else {
                    m_parent_entity_map[parent_entity].push_back(entity);
                }
            }
            else {
                // default to -1 when there is no parent
                if (m_parent_entity_map.find(-1) == m_parent_entity_map.end()) {
                    m_parent_entity_map[-1] = std::vector<EntityID>{entity};
                }
                else {
                    m_parent_entity_map[-1].push_back(entity);
                }
            }
        }
    }

    void YamlSceneSerializer::SerializeEntities(YAML::Emitter &out, EntityID parent_entity) {
        assert(m_parent_entity_map.find(parent_entity) != m_parent_entity_map.end() && "Parent entity not found.");

        out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

        // Iterate over the root entities
        for (EntityID entity : m_parent_entity_map[parent_entity]) {
            SerializeEntity(out, entity);
        }

        out << YAML::EndSeq;
    }

    void YamlSceneSerializer::SerializeEntity(YAML::Emitter &out, EntityID entity) {
        LOG(LoggingType::INFO, "Serializing EntityID \"" + std::to_string(entity) + "\"");

        out << YAML::BeginMap;
        out << YAML::Key << "Entity" << YAML::Value << YAML::BeginMap;

        // Serialize entity's components
        std::vector<IComponent *> components = g_ecs.GetAllComponents(entity);
        for (int i = 0; i < components.size(); i++) {
            LOG(LoggingType::INFO, "Serializing Component \"" + std::string(components[i]->GetName()) + "\"");

            // Component Name first
            out << YAML::Key << components[i]->GetName() << YAML::Value;

            // Component data
            out << YAML::BeginMap;
            YamlComponentWriter writer(out);
            components[i]->Serialize(writer);
            out << YAML::EndMap;
        }

        if (m_parent_entity_map.find(entity) != m_parent_entity_map.end()) {
            SerializeEntities(out, entity);
        }

        out << YAML::EndMap;
        out << YAML::EndMap;
    }

    void YamlSceneSerializer::Deserialize(std::filesystem::path filepath) {
        assert(!filepath.empty() && "Current filepath is empty.");

        // Parse the YAML data
        YAML::Node scene = YAML::LoadFile(filepath.string());

        DeserializeEntities(scene, -1);
    }

    void YamlSceneSerializer::DeserializeEntity(const YAML::Node &node, EntityID parent_entity, EntityID entity) {
        LOG(LoggingType::INFO, "Loading EntityID \"" + std::to_string(entity) + "\"");

        // Iterate over the components
        for (const auto &components : node["Entity"]) {
            // Get the component type name
            std::string component_name = components.first.as<std::string>();

            // Skip the "Entities" nested node, this isn't a component
            if (component_name == "Entities") {
                DeserializeEntities(components.second, entity);
                continue;
            }

            // Get the component data
            YAML::Node component = components.second;

            if (g_ecs.IsComponentRegistered(component_name)) {
                LOG(LoggingType::INFO, "Loading component: " + component_name);
                Serializers::YamlComponentReader reader(component);
                m_component_factory->CreateComponent(component_name, reader, parent_entity, entity);
            }
            else {
                LOG(LoggingType::FATAL, "Component " + component_name + " is not registered.");
            }
        }
    }

    void YamlSceneSerializer::DeserializeEntities(const YAML::Node &node, EntityID parent_entity) {
        // Iterate over the entities
        for (const YAML::Node &entity_node : parent_entity != -1 ? node : node["Entities"]) {
            // Create a new entity
            EntityID entity = g_ecs.CreateEntity();

            DeserializeEntity(entity_node, parent_entity, entity);
        }
    }
} // namespace HBE::Serializers