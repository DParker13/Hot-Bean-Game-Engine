#include "serialization_manager.hpp"

namespace HBE::Managers {

    SerializationManager::SerializationManager(std::shared_ptr<ECSManager> ecs_manager,
                                               std::shared_ptr<LoggingManager> logging_manager,
                                               std::shared_ptr<IComponentFactory> component_factory)
        : m_ecs_manager(ecs_manager), m_logging_manager(logging_manager), m_component_factory(component_factory) {}

    void SerializationManager::LoadScene(std::shared_ptr<Scene> scene) {
        LoadScene(scene, false);
    }

    void SerializationManager::LoadScene(std::shared_ptr<Scene> scene, bool save_to_file) {
        assert(scene && "Scene is null.");

        try {
            // Unload current scene if a new one is being loaded
            if (m_current_scene && m_current_scene != scene) {
                UnloadScene(save_to_file);
            }

            m_current_scene = scene;
        
            LOG_CORE(LoggingType::INFO, "Loading scene \"" + m_current_scene->m_name + "\" from file: ");
            LOG_CORE(LoggingType::INFO, "Scene path: " + m_current_scene->m_scene_path);

            // Attempt to load scene from file
            if (!std::filesystem::exists(m_current_scene->m_scene_path)) {
                LOG_CORE(LoggingType::FATAL, "Scene file does not exist: "+ m_current_scene->m_scene_path);
                throw std::runtime_error("Scene file does not exist: "+ m_current_scene->m_scene_path);
            }

            m_current_scene->SetupSystems();

            DeserializeScene(m_current_scene->m_scene_path);

            m_ecs_manager->IterateSystems(GameLoopState::OnStart);

            LOG_CORE(LoggingType::INFO, "Scene loaded.");
        } catch (const YAML::Exception& e) {
            LOG_CORE(LoggingType::ERROR, "Error parsing YAML file: " + (std::string)e.what());
        }

        m_current_scene->SetupScene();
    }

    void SerializationManager::UnloadScene(bool save_to_file) {
        assert(m_current_scene && "Current scene is null.");

        try {
            LOG_CORE(LoggingType::INFO, "Unloading scene \"" + m_current_scene->m_name + "\" to file");
            LOG_CORE(LoggingType::INFO, "Scene path: " + m_current_scene->m_scene_path);

            // Attempt to serialize scene to file
            if (save_to_file) {
                SerializeScene(m_current_scene->m_scene_path);
            }

            // Destroy all entities
            for (Entity entity = 0; entity < m_ecs_manager->EntityCount(); entity++) {
                m_ecs_manager->DestroyEntity(entity);
            }

            // TODO: Unload all systems

            LOG_CORE(LoggingType::INFO, "Scene \"" + m_current_scene->m_name + "\" serialized.");
        } catch (const YAML::Exception& e) {
            std::cerr << "Error serializing to YAML file: " << e.what() << std::endl;
        }
    }

    void SerializationManager::RegisterScene(std::shared_ptr<Scene> scene) {
        assert(scene && "Scene is null.");
        assert(m_scenes.find(scene->m_name) == m_scenes.end() && "Scene with that name already exists.");

        m_scenes.emplace(scene->m_name, scene);
    }

    void SerializationManager::RemoveScene(std::shared_ptr<Scene> scene, bool save_to_file) {
        assert(scene && "Scene is null.");

        RemoveScene(scene->m_name, save_to_file);
    }

    void SerializationManager::RemoveScene(std::string name, bool save_to_file) {
        assert(m_scenes.find(name) != m_scenes.end() && "Scene isn't registered.");

        if (m_current_scene->m_name == name) {
            UnloadScene(save_to_file);
        }

        m_scenes.erase(name);
    }

    void SerializationManager::SwitchScene(std::shared_ptr<Scene> scene) {
        assert(scene && "Scene is null.");

        SwitchScene(scene->m_name);
    }

    void SerializationManager::SwitchScene(std::string name) {
        assert(m_scenes.find(name) != m_scenes.end() && "Scene with that name does not exist.");
        LOG_CORE(LoggingType::INFO, "Switching to scene: " + name);

        // Loads the new scene
        LoadScene(m_scenes[name]);
    }

    void SerializationManager::SerializeScene(const std::string& filepath) {
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
    void SerializationManager::MapParentEntities() {
        for (Entity entity = 0; entity < m_ecs_manager->EntityCount(); entity++) {
            if (m_ecs_manager->HasComponent<Components::Transform2D>(entity)) {
                Entity parent_entity = m_ecs_manager->GetComponent<Components::Transform2D>(entity).m_parent;

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

    void SerializationManager::SerializeEntities(YAML::Emitter& out, Entity parent_entity) {
        assert(m_parent_entity_map.find(parent_entity) != m_parent_entity_map.end() && "Parent entity not found.");

        out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

        // Iterate over the root entities
        for (Entity entity : m_parent_entity_map[parent_entity]) {
            SerializeEntity(out, entity);
        }

        out << YAML::EndSeq;
    }

    void SerializationManager::SerializeEntity(YAML::Emitter& out, Entity entity) {
        LOG_CORE(LoggingType::INFO, "Serializing Entity \"" + std::to_string(entity) + "\"");

        out << YAML::BeginMap;
        out << YAML::Key << "Entity" << YAML::Value << YAML::BeginMap;

        // Serialize entity's components
        std::vector<Component*> components = m_ecs_manager->GetAllComponents(entity);
        for (int i = 0; i < components.size(); i++) {
            LOG_CORE(LoggingType::INFO, "Serializing Component \"" + components[i]->GetName() + "\"");

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

    void SerializationManager::DeserializeScene(const std::string& filepath) {
        assert(!filepath.empty() && "Current filepath is empty.");

        // Parse the YAML data
        YAML::Node scene = YAML::LoadFile(filepath);
        
        DeserializeEntities(scene, -1);
    }

    void SerializationManager::DeserializeEntity(const YAML::Node& node, Entity parent_entity, Entity entity) {
        LOG_CORE(LoggingType::INFO,
            "Loading Entity \"" + std::to_string(entity) + "\"");

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

            if (m_ecs_manager->IsComponentRegistered(component_name)) {
                LOG_CORE(LoggingType::INFO, "Loading component: " + component_name);
                m_component_factory->CreateComponent(component_name, component, parent_entity, entity);
            }
            else {
                LOG_CORE(LoggingType::FATAL, "Component " + component_name + " is not registered.");
                throw std::runtime_error("Component " + component_name + " is not registered.");
            }
        }
    }

    void SerializationManager::DeserializeEntities(const YAML::Node& node, Entity parent_entity) {
        // Iterate over the entities
        for (const YAML::Node& entity_node : parent_entity != -1 ? node : node["Entities"]) {
            // Create a new entity
            Entity entity = m_ecs_manager->CreateEntity();

            DeserializeEntity(entity_node, parent_entity, entity);
        }
    }
}