#pragma once

#include <memory>

#include "../components/component_factory.hpp"

using namespace Core::ECS;

namespace Core {
    namespace Managers {
        class SerializationManager {
            public:
                /// @brief Map of names to scenes
                std::unordered_map<std::string, std::shared_ptr<Scene>> m_scenes;
    
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
                std::shared_ptr<ECSManager> m_ecs_manager;
                std::shared_ptr<LoggingManager> m_logging_manager;

                /// @brief Current scene
                std::shared_ptr<Scene> m_current_scene;
                std::unordered_map<Entity, std::vector<Entity>> m_parent_entity_map;

                // void UnloadScene();
                
                void SerializeScene(const std::string& filepath);
                void SerializeEntities(YAML::Emitter& out, Entity parent_entity);
                void SerializeEntity(YAML::Emitter& out, Entity entity);
                void MapParentEntities();

                void DeserializeScene(const std::string& filepath);
                void DeserializeEntities(const YAML::Node& node, Entity parent_entity);
                void DeserializeEntity(const YAML::Node& node, Entity parent_entity, Entity entity);
        };
    }
}