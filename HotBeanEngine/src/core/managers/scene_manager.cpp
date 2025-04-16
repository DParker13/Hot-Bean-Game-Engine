#include "scene_manager.hpp"

namespace Core {
    namespace Managers {

        SceneManager::SceneManager(std::shared_ptr<ECSManager> ecsManager)
            : _ecsManager(ecsManager) {}

        void SceneManager::LoadScene(std::shared_ptr<Scene> scene) {
            assert(scene && "Scene is null.");

            if (_currentScene && _currentScene != scene) {
                UnloadScene();
            }
            _currentScene = scene;

            LoadScene();
        }

        void SceneManager::RegisterScene(std::shared_ptr<Scene> scene) {
            assert(scene && "Scene is null.");
            assert(_scenes.find(scene->_name) == _scenes.end() && "Scene with that name already exists.");
    
            _scenes.emplace(scene->_name, scene);
        }

        void SceneManager::RemoveScene(std::shared_ptr<Scene> scene) {
            assert(scene && "Scene is null.");

            RemoveScene(scene->_name);
        }

        void SceneManager::RemoveScene(std::string name) {
            assert(_scenes.find(name) != _scenes.end() && "Scene isn't registered.");

            if (_currentScene->_name == name) {
                UnloadScene();
            }

            _scenes.erase(name);
        }

        void SceneManager::SwitchScene(std::shared_ptr<Scene> scene) {
            assert(scene && "Scene is null.");

            SwitchScene(scene->_name);
        }

        void SceneManager::SwitchScene(std::string name) {
            assert(_scenes.find(name) != _scenes.end() && "Scene with that name does not exist.");

            // Unloads the current scene
            UnloadScene();

            // Sets the current scene to the new scene using the name
            _currentScene = _scenes[name];

            // Loads the new scene
            LoadScene();
        }

        void SceneManager::LoadScene() {
            assert(_currentScene && "Current scene is null.");

            try {
                // Attempt to load scene from file
                if (!std::filesystem::exists(_currentScene->_scene_path)) {
                    _currentScene->_scene_path = std::filesystem::current_path() / "scenes" / _currentScene->_scene_path;
                }

                // Parse the YAML data
                YAML::Node scene = YAML::LoadFile(_currentScene->_scene_path.string());

                if (scene.IsSequence()) {
                    // Iterate over the entities
                    for (YAML::const_iterator entities = scene.begin(); entities != scene.end(); ++entities) {
                        // Get the entity name
                        Entity entity = _ecsManager->CreateEntity();

                        // Get the components
                        YAML::Node components = entities->second;

                        // Iterate over the components
                        for (YAML::const_iterator it2 = components.begin(); it2 != components.end(); ++it2) {
                            // Get the component type name
                            std::string componentType = it2->first["type"].as<std::string>();
                            
                            // Get the component data
                            YAML::Node component = it2->second;

                            // Create the component
                            //_ecsManager->AddComponent(currentEntity);

                            // Set the component data
                            //_ecsManager->GetComponent(currentEntity);
                        }
                    }
                }
            } catch (const YAML::Exception& e) {
                std::cerr << "Error parsing YAML file: " << e.what() << std::endl;
            }

            //_currentScene->SetupScene();
        }

        void SceneManager::UnloadScene() {
            assert(_currentScene && "Current scene is null.");

            //_currentScene->UnloadScene(_app);
        }
    }
}