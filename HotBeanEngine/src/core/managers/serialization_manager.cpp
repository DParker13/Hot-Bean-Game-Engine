#include "serialization_manager.hpp"

namespace Core::Managers {

    SerializationManager::SerializationManager(std::shared_ptr<ECSManager> ecs_manager, std::shared_ptr<LoggingManager> logging_manager)
        : _ecs_manager(ecs_manager), _logging_manager(logging_manager) {}

    void SerializationManager::LoadScene(std::shared_ptr<Scene> scene) {
        assert(scene && "Scene is null.");

        try {
            // Unload current scene if a new one is being loaded
            if (_current_scene && _current_scene != scene) {
                UnloadScene();
            }

            _current_scene = scene;
        
            _logging_manager->Log(LoggingType::INFO, "Loading scene \"" + _current_scene->_name + "\" from file: ");
            _logging_manager->Log(LoggingType::INFO, "Scene path: " + _current_scene->_scene_path);

            // Attempt to load scene from file
            if (!std::filesystem::exists(_current_scene->_scene_path)) {
                _logging_manager->Log(LoggingType::FATAL, "Scene file does not exist: "+ _current_scene->_scene_path);
                throw std::runtime_error("Scene file does not exist: "+ _current_scene->_scene_path);
            }

            DeserializeScene(_current_scene->_scene_path);

            _logging_manager->Log(LoggingType::INFO, "Scene loaded.");
        } catch (const YAML::Exception& e) {
            _logging_manager->Log(LoggingType::ERROR, "Error parsing YAML file: " + (std::string)e.what());
        }

        _current_scene->SetupScene();
    }

    void SerializationManager::UnloadScene() {
        assert(_current_scene && "Current scene is null.");

        try {
            _logging_manager->Log(LoggingType::INFO, "Unloading scene \"" + _current_scene->_name + "\" to file");
            _logging_manager->Log(LoggingType::INFO, "Scene path: " + _current_scene->_scene_path);

            // Attempt to serialize scene to file
            SerializeScene("C:\\Users\\danie\\Documents\\GitHub\\HotBeanEngine\\bin\\scenes\\test-saving.yaml");

            // Destroy all entities
            for (Entity entity = 0; entity < _ecs_manager->EntityCount(); entity++) {
                _ecs_manager->DestroyEntity(entity);
            }

            _logging_manager->Log(LoggingType::INFO, "Scene \"" + _current_scene->_name + "\" serialized.");
        } catch (const YAML::Exception& e) {
            std::cerr << "Error serializing to YAML file: " << e.what() << std::endl;
        }

        // Unload any manually coded entities from the scene
        _current_scene->UnloadScene();
    }

    void SerializationManager::RegisterScene(std::shared_ptr<Scene> scene) {
        assert(scene && "Scene is null.");
        assert(_scenes.find(scene->_name) == _scenes.end() && "Scene with that name already exists.");

        _scenes.emplace(scene->_name, scene);
    }

    void SerializationManager::RemoveScene(std::shared_ptr<Scene> scene) {
        assert(scene && "Scene is null.");

        RemoveScene(scene->_name);
    }

    void SerializationManager::RemoveScene(std::string name) {
        assert(_scenes.find(name) != _scenes.end() && "Scene isn't registered.");

        if (_current_scene->_name == name) {
            UnloadScene();
        }

        _scenes.erase(name);
    }

    void SerializationManager::SwitchScene(std::shared_ptr<Scene> scene) {
        assert(scene && "Scene is null.");

        SwitchScene(scene->_name);
    }

    void SerializationManager::SwitchScene(std::string name) {
        assert(_scenes.find(name) != _scenes.end() && "Scene with that name does not exist.");
        _logging_manager->Log(LoggingType::INFO, "Switching to scene: " + name);

        // Loads the new scene
        LoadScene(_scenes[name]);
    }

    void SerializationManager::SerializeScene(const std::string& filepath) {
        assert(!filepath.empty() && "Current filepath is empty.");

        YAML::Emitter out = YAML::Emitter();

        out << YAML::BeginMap;
        out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

        // Iterate over the entities
        for (Entity entity = 0; entity < _ecs_manager->EntityCount(); entity++) {
            SerializeEntity(out, entity);
        }

        out << YAML::EndSeq;
        out << YAML::EndMap;

        std::ofstream file(filepath);
        file << out.c_str();
    }

    void SerializationManager::SerializeEntity(YAML::Emitter& out, Entity entity) {
        _logging_manager->Log(LoggingType::INFO, "Serializing Entity \"" + std::to_string(entity) + "\"");

        out << YAML::BeginMap;
        out << YAML::Key << "Entity" << YAML::Value << YAML::BeginMap;

        // Serialize entity's components
        std::vector<Component*> components = _ecs_manager->GetAllComponents(entity);
        for (int i = 0; i < components.size(); i++) {
            _logging_manager->Log(LoggingType::INFO, "Serializing Component \"" + components[i]->GetName() + "\"");

            // Component Name first
            out << YAML::Key << components[i]->GetName() << YAML::Value;

            // Component data
            out << YAML::BeginMap;
            components[i]->Serialize(out);
            out << YAML::EndMap;
        }

        out << YAML::EndMap;
        out << YAML::EndMap;
    }

    void SerializationManager::DeserializeScene(const std::string& filepath) {
        assert(!filepath.empty() && "Current filepath is empty.");

        // Parse the YAML data
        YAML::Node scene = YAML::LoadFile(filepath);
        
        // Iterate over the entities
        for (const YAML::Node& entities : scene["Entities"]) {
            // Get the entity name
            Entity entity = _ecs_manager->CreateEntity();

            DeserializeEntity(entities, entity);
        }
    }

    void SerializationManager::DeserializeEntity(const YAML::Node& node, Entity entity) {
        _logging_manager->Log(LoggingType::INFO,
            "Loading Entity \"" + std::to_string(entity) + "\"");

        // Iterate over the components
        for (const auto& components : node["Entity"]) {
            // Get the component type name
            std::string component_name = components.first.as<std::string>();

            // Get the component data
            YAML::Node component = components.second;

            if (_ecs_manager->IsComponentRegistered(component_name)) {
                _logging_manager->Log(LoggingType::INFO, "Loading component: " + component_name);
                Core::Application::ComponentFactory::CreateComponent(*_ecs_manager, component_name, component, entity);
            }
            else {
                _logging_manager->Log(LoggingType::FATAL, "Component " + component_name + " is not registered.");
                throw std::runtime_error("Component " + component_name + " is not registered.");
            }
        }
    }
}