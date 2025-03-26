#include "scene_manager.hpp"

namespace Core {
    namespace Managers {

        SceneManager::SceneManager(App& app) : _app(app) {}

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

            _currentScene->SetupScene(_app);
        }

        void SceneManager::UnloadScene() {
            assert(_currentScene && "Current scene is null.");

            _currentScene->UnloadScene();
        }
    }
}