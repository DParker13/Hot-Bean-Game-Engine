#pragma once

#include <yaml-cpp/yaml.h>
#include <memory>

#include "ecs_manager.hpp"

using namespace Core::ECS;

namespace Core {
    namespace Managers {
        class SceneManager {
            public:
                /// @brief Map of names to scenes
                std::unordered_map<std::string, std::shared_ptr<Scene>> _scenes;
    
                SceneManager(std::shared_ptr<ECSManager> ecsManager);
                ~SceneManager() = default;
    
                void LoadScene(std::shared_ptr<Scene> scene);
                void RegisterScene(std::shared_ptr<Scene> scene);
                void RemoveScene(std::string name);
                void RemoveScene(std::shared_ptr<Scene> scene);
                void SwitchScene(std::shared_ptr<Scene> scene);
                void SwitchScene(std::string name);

            private:
                /// @brief  Reference to the ecs manager
                std::shared_ptr<ECSManager> _ecsManager;
                std::shared_ptr<Scene> _currentScene;

                void LoadScene();
                void UnloadScene();
        };
    }
}