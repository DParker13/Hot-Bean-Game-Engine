#pragma once

#include <memory>

#include "../components/component_factory.hpp"

using namespace Core::ECS;

namespace Core {
    namespace Managers {
        class SerializationManager {
            public:
                /// @brief Map of names to scenes
                std::unordered_map<std::string, std::shared_ptr<Scene>> _scenes;
    
                SerializationManager(std::shared_ptr<ECSManager> ecs_manager, std::shared_ptr<LoggingManager> logging_manager);
                ~SerializationManager() = default;
    
                void LoadScene(std::shared_ptr<Scene> scene);
                void UnloadScene();

                void RegisterScene(std::shared_ptr<Scene> scene);
                void RemoveScene(std::string name);
                void RemoveScene(std::shared_ptr<Scene> scene);
                void SwitchScene(std::shared_ptr<Scene> scene);
                void SwitchScene(std::string name);

            private:
                /// @brief  Reference to the ecs manager
                std::shared_ptr<ECSManager> _ecs_manager;
                std::shared_ptr<LoggingManager> _logging_manager;

                /// @brief Current scene
                std::shared_ptr<Scene> _current_scene;

                // void UnloadScene();
                
                void SerializeScene(const std::string& filepath);
                void SerializeEntity(YAML::Emitter& out, Entity entity);
                void DeserializeScene(const std::string& filepath);
                void DeserializeEntity(const YAML::Node& node, Entity entity);
        };
    }
}