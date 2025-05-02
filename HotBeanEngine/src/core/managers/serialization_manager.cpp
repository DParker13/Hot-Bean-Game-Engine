#include "serialization_manager.hpp"

namespace Core::Managers {

    SerializationManager::SerializationManager(std::shared_ptr<ECSManager> ecs_manager, std::shared_ptr<LoggingManager> logging_manager)
        : _ecs_manager(ecs_manager), _logging_manager(logging_manager) {}

    void SerializationManager::LoadScene(std::shared_ptr<Scene> scene) {
        assert(scene && "Scene is null.");

        if (_current_scene && _current_scene != scene) {
            UnloadScene();
        }
        _current_scene = scene;

        LoadScene();
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

        // Unloads the current scene
        UnloadScene();

        // Sets the current scene to the new scene using the name
        _current_scene = _scenes[name];

        // Loads the new scene
        LoadScene();
    }

    void SerializationManager::LoadScene() {
        assert(_current_scene && "Current scene is null.");

        try {
            _logging_manager->Log(LoggingType::INFO, "Loading scene from file: " + _current_scene->_name);
            _logging_manager->Log(LoggingType::INFO, "Scene path: " + _current_scene->_scene_path);

            // Attempt to load scene from file
            if (!std::filesystem::exists(_current_scene->_scene_path)) {
                _logging_manager->Log(LoggingType::FATAL, "Scene file ( "+ _current_scene->_name +" ) does not exist.");
                throw std::runtime_error("Scene file ( "+ _current_scene->_name +" ) does not exist.");
            }

            // Parse the YAML data
            YAML::Node scene = YAML::LoadFile(_current_scene->_scene_path);

            // Iterate over the entities
            for (const auto& entities : scene["Entities"]) {
                // Get the entity name
                Entity entity = _ecs_manager->CreateEntity();

                _logging_manager->Log(LoggingType::INFO,
                    "Loading Entity (" + std::to_string(entity) + ") from file");

                // Iterate over the components
                for (const auto& components : entities["Entity"]) {
                    // Get the component type name
                    std::string component_name = components.first.as<std::string>();

                    // Get the component data
                    YAML::Node component = components.second;

                    if (_ecs_manager->IsComponentRegistered(component_name)) {
                        _logging_manager->Log(LoggingType::INFO, "Loading component: " + component_name);
                        ComponentRegister::CreateComponent(*_ecs_manager, component_name, component, entity);
                    }
                    else {
                        _logging_manager->Log(LoggingType::FATAL, "Component " + component_name + " is not registered.");
                        throw std::runtime_error("Component " + component_name + " is not registered.");
                    }
                }
            }

            _logging_manager->Log(LoggingType::INFO, "Scene loaded.");
        } catch (const YAML::Exception& e) {
            std::cerr << "Error parsing YAML file: " << e.what() << std::endl;
        }

        _current_scene->SetupScene();
    }

    void SerializationManager::UnloadScene() {
        assert(_current_scene && "Current scene is null.");

        try {
            _logging_manager->Log(LoggingType::INFO, "Unloading scene to file: " + _current_scene->_name);
            _logging_manager->Log(LoggingType::INFO, "Scene path: " + _current_scene->_scene_path);

            YAML::Emitter out = YAML::Emitter();

            out << YAML::BeginMap;
            out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

            // Iterate over the entities
            for (Entity entity = 0; entity < _ecs_manager->EntityCount(); entity++) {
                out << YAML::BeginMap;
                out << YAML::Key << "Entity" << YAML::Value << YAML::BeginSeq;

                // Iterate over the components
                std::vector<Component*> components = _ecs_manager->GetAllComponents(entity);
                for (int i = 0; i < components.size(); i++) {
                    out << YAML::Key << components[i]->GetName() << YAML::Value;

                    out << YAML::BeginMap;
                    components[i]->Serialize(out);
                    out << YAML::EndMap;
                }

                out << YAML::EndSeq;
            }

            out << YAML::EndSeq;
            out << YAML::EndMap;

            std::ofstream file(_current_scene->_scene_path);
            file << out.c_str();

            _logging_manager->Log(LoggingType::INFO, "Scene loaded.");
        } catch (const YAML::Exception& e) {
            std::cerr << "Error parsing YAML file: " << e.what() << std::endl;
        }

        //_current_scene->UnloadScene(_app);
    }
}