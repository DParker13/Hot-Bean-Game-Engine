#include <HotBeanEngine/defaults/default_scene_serializer.hpp>

namespace HBE::Default {
    DefaultSceneSerializer::DefaultSceneSerializer(std::shared_ptr<IComponentFactory> component_factory)
        : m_component_factory(component_factory) {}

    void DefaultSceneSerializer::Serialize(const std::string& filepath) {
        assert(!filepath.empty() && "Current filepath is empty.");

        YAML::Emitter out = YAML::Emitter();

        MapParentEntities();

        out << YAML::BeginMap;
        SerializeEntities(out, -1);
        out << YAML::EndMap;

        std::ofstream file(filepath);
        file << out.c_str();
    }

    // TODO: Replace this with a better solution. Maybe use the TransformSystem.m_entities member instead
    void DefaultSceneSerializer::MapParentEntities() {
        for (Entity entity = 0; entity < g_ecs.EntityCount(); entity++) {
            if (g_ecs.HasComponent<Transform2D>(entity)) {
                Entity parent_entity = g_ecs.GetComponent<Transform2D>(entity).m_parent;

                if (m_parent_entity_map.find(parent_entity) == m_parent_entity_map.end()) {
                    m_parent_entity_map[parent_entity] = std::vector<Entity> { entity };
                }
                else {
                    m_parent_entity_map[parent_entity].push_back(entity);
                }
            }
            else {
                // default to -1 when there is no parent
                if (m_parent_entity_map.find(-1) == m_parent_entity_map.end()) {
                    m_parent_entity_map[-1] = std::vector<Entity> { entity };
                }
                else {
                    m_parent_entity_map[-1].push_back(entity);
                }
            }
        }
    }

    void DefaultSceneSerializer::SerializeEntities(YAML::Emitter& out, Entity parent_entity) {
        assert(m_parent_entity_map.find(parent_entity) != m_parent_entity_map.end() && "Parent entity not found.");

        out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

        // Iterate over the root entities
        for (Entity entity : m_parent_entity_map[parent_entity]) {
            SerializeEntity(out, entity);
        }

        out << YAML::EndSeq;
    }

    void DefaultSceneSerializer::SerializeEntity(YAML::Emitter& out, Entity entity) {
        LOG(LoggingType::INFO, "Serializing Entity \"" + std::to_string(entity) + "\"");

        out << YAML::BeginMap;
        out << YAML::Key << "Entity" << YAML::Value << YAML::BeginMap;

        // Serialize entity's components
        std::vector<Component*> components = g_ecs.GetAllComponents(entity);
        for (int i = 0; i < components.size(); i++) {
            LOG(LoggingType::INFO, "Serializing Component \"" + components[i]->GetName() + "\"");

            // Component Name first
            out << YAML::Key << components[i]->GetName() << YAML::Value;

            // Component data
            out << YAML::BeginMap;
            components[i]->Serialize(out);
            out << YAML::EndMap;
        }

        if (m_parent_entity_map.find(entity) != m_parent_entity_map.end()) {
            SerializeEntities(out, entity);
        }

        out << YAML::EndMap;
        out << YAML::EndMap;
    }

    void DefaultSceneSerializer::Deserialize(const std::string& filepath) {
        assert(!filepath.empty() && "Current filepath is empty.");

        // Parse the YAML data
        YAML::Node scene = YAML::LoadFile(filepath);
        
        DeserializeEntities(scene, -1);
    }

    void DefaultSceneSerializer::DeserializeEntity(const YAML::Node& node, Entity parent_entity, Entity entity) {
        LOG(LoggingType::INFO, "Loading Entity \"" + std::to_string(entity) + "\"");

        // Iterate over the components
        for (const auto& components : node["Entity"]) {
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
                m_component_factory->CreateComponentFromYAML(component_name, component, parent_entity, entity);
            }
            else {
                LOG(LoggingType::FATAL, "Component " + component_name + " is not registered.");
            }
        }
    }

    void DefaultSceneSerializer::DeserializeEntities(const YAML::Node& node, Entity parent_entity) {
        // Iterate over the entities
        for (const YAML::Node& entity_node : parent_entity != -1 ? node : node["Entities"]) {
            // Create a new entity
            Entity entity = g_ecs.CreateEntity();

            DeserializeEntity(entity_node, parent_entity, entity);
        }
    }

    bool DefaultSceneSerializer::FileExists(const std::string& filepath) {
        return std::filesystem::exists(filepath);
    }
}