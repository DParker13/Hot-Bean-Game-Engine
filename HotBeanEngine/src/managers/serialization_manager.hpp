#pragma once

#include <filesystem>
#include <memory>

#include "../components/component_factory.hpp"
#include "../components/default_components.hpp"

using namespace HBE::Application;
using namespace HBE::Core;

namespace HBE::Managers {
    class SerializationManager {
        public:
            /// @brief Map of names to scenes
            std::unordered_map<std::string, std::shared_ptr<Scene>> m_scenes;

            SerializationManager(std::shared_ptr<ECSManager> ecs_manager,
                                    std::shared_ptr<LoggingManager> logging_manager,
                                    std::shared_ptr<IComponentFactory> component_factory);
            ~SerializationManager() = default;

            void LoadScene(std::shared_ptr<Scene> scene);
            void LoadScene(std::shared_ptr<Scene> scene, bool save_to_file);
            void UnloadScene(bool save_to_file);

            void RegisterScene(std::shared_ptr<Scene> scene);
            void RemoveScene(std::string name, bool save_to_file);
            void RemoveScene(std::shared_ptr<Scene> scene, bool save_to_file);
            void SwitchScene(std::shared_ptr<Scene> scene);
            void SwitchScene(std::string name);

        private:
            std::shared_ptr<ECSManager> m_ecs_manager;
            std::shared_ptr<LoggingManager> m_logging_manager;
            std::shared_ptr<IComponentFactory> m_component_factory;

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