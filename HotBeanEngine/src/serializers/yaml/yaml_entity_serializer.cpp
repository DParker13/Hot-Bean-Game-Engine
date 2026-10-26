/**
 * @file yaml_entity_serializer.cpp
 * @author Daniel Parker (DParker13)
 * @brief YAML-backed implementation of the ISerializer interface.
 * @version 1.0
 * @date 2025-10-11
 *
 * @copyright Copyright (c) 2025
 */

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/components/miscellaneous/transform_2d.hpp>
#include <HotBeanEngine/serializers/yaml/yaml_entity_serializer.hpp>
#include <HotBeanEngine/serializers/yaml/yaml_serialization_reader.hpp>
#include <HotBeanEngine/serializers/yaml/yaml_serialization_writer.hpp>

namespace HBE::Serializers {
    using namespace Core;
    using namespace Components;

    void YamlEntitySerializer::Serialize(std::filesystem::path filepath, Core::ISerializable &object, bool append) {
        assert(!filepath.empty() && "Current filepath is empty.");

        try {
            YAML::Emitter out;
            out.SetIndent(2);
            YamlWriter writer(out);

            m_parent_entity_map.clear();
            MapParentEntities();

            writer << YAML::BeginMap;
            SerializeEntities(writer, -1);
            writer << YAML::EndMap;

            writer.WriteToFile(filepath, append ? ISerializationWriter::FileWriteMode::Append
                                                : ISerializationWriter::FileWriteMode::Overwrite);
        } catch (const std::exception &e) {
            LOG(Core::LoggingType::ERROR,
                "Failed to serialize YAML scene: " + filepath.string() + " with error: " + e.what());
        } catch (...) {
            LOG(Core::LoggingType::ERROR, "Failed to serialize YAML scene: " + filepath.string());
        }
    }

    void YamlEntitySerializer::MapParentEntities() {
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

    // TODO: Replace this with a better solution. Maybe use the TransformSystem.m_entities member instead
    void YamlEntitySerializer::SerializeEntities(YamlWriter &out, EntityID parent_entity) {
        assert(m_parent_entity_map.find(parent_entity) != m_parent_entity_map.end() && "Parent entity not found.");

        out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

        // Iterate over the root entities
        for (EntityID entity : m_parent_entity_map[parent_entity]) {
            SerializeEntity(out, entity);
        }

        out << YAML::EndSeq;
    }

    void YamlEntitySerializer::SerializeEntity(YamlWriter &out, EntityID entity) {
        LOG(LoggingType::INFO, "Serializing EntityID \"" + std::to_string(entity) + "\"");

        out << YAML::BeginMap;
        out << YAML::Key << "Entity" << YAML::Value << YAML::BeginMap;

        // Serialize entity's components
        std::vector<IComponent *> components = g_ecs.GetAllComponents(entity);
        for (int i = 0; i < components.size(); i++) {
            LOG(LoggingType::INFO, "Serializing Component \"" + std::string(components[i]->GetName()) + "\"");

            YamlWriter writer(out);
            components[i]->Serialize(writer);
        }

        if (m_parent_entity_map.find(entity) != m_parent_entity_map.end()) {
            SerializeEntities(out, entity);
        }

        out << YAML::EndMap;
        out << YAML::EndMap;
    }

    void YamlEntitySerializer::Deserialize(std::filesystem::path filepath, Core::ISerializable &object) {
        assert(!filepath.empty() && "Current filepath is empty.");

        // Parse the YAML data
        YAML::Node scene = YAML::LoadFile(filepath.string());

        YamlReader reader(scene, filepath);
        DeserializeEntities(reader, -1);
    }

    void YamlEntitySerializer::DeserializeEntity(const YamlReader &reader, EntityID parent_entity, EntityID entity) {
        LOG(LoggingType::INFO, "Loading EntityID \"" + std::to_string(entity) + "\"");

        YamlReader component_reader = reader["Entity"];

        // Iterate over the components
        for (const auto &components : component_reader) {
            // Get the component type name
            std::string component_name = components.first.as<std::string>();

            // Skip the "Entities" nested node, this isn't a component
            if (component_name == "Entities") {
                YamlReader entities_reader(components.second, reader.GetSourcePath());
                DeserializeEntities(entities_reader, entity);
                continue;
            }

            // Get the component data
            if (g_ecs.IsComponentRegistered(component_name)) {
                LOG(LoggingType::INFO, "Loading component: " + component_name);
                g_app.GetComponentFactory()->CreateComponent(component_name, component_reader, parent_entity, entity);
            }
            else {
                LOG(LoggingType::FATAL, "Component " + component_name + " is not registered.");
            }
        }
    }

    void YamlEntitySerializer::DeserializeEntities(const YamlReader &reader, EntityID parent_entity) {
        const YamlReader entities = parent_entity != -1 ? reader : reader["Entities"];

        for (size_t index = 0; index < entities.Size(); ++index) {
            YamlReader entity_reader = entities[index];
            // Create a new entity
            EntityID entity = g_ecs.CreateEntity();

            DeserializeEntity(entity_reader, parent_entity, entity);
        }
    }
} // namespace HBE::Serializers