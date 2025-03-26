#pragma once

#include <memory>

#include "../ecs/all_ecs.hpp"

using namespace Core::ECS;
using namespace Core::Application;

namespace Core {
    namespace Managers {
        class SceneManager {
            public:
                /// @brief  Reference to the application
                /// TODO: Think of a better way to do this without referencing App
                App& _app;

                /// @brief Map of names to scenes
                std::unordered_map<std::string, std::shared_ptr<Scene>> _scenes;
    
                SceneManager(App& app);
                ~SceneManager() = default;
    
                void LoadScene(std::shared_ptr<Scene> scene);
                void RegisterScene(std::shared_ptr<Scene> scene);
                void RemoveScene(std::string name);
                void RemoveScene(std::shared_ptr<Scene> scene);
                void SwitchScene(std::shared_ptr<Scene> scene);
                void SwitchScene(std::string name);

            private:
                std::shared_ptr<Scene> _currentScene;

                void LoadScene();
                void UnloadScene();
        };
    }
}