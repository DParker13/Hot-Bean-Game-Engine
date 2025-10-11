#pragma once

#include <fstream>
#include <filesystem>

#include <HotBeanEngine/defaults/components/default_component_factory.hpp>

using namespace HBE::Default::Components;

namespace HBE::Default {

    class DefaultSceneSerializer : public ISerializer {
        private:
            std::unordered_map<Entity, std::vector<Entity>> m_parent_entity_map;
            std::shared_ptr<IComponentFactory> m_component_factory;

        public:
            DefaultSceneSerializer(std::shared_ptr<IComponentFactory> component_factory);

            void Serialize(const std::string& filepath) override;
            void Deserialize(const std::string& filepath) override;
            bool FileExists(const std::string& filepath) override;

        private:
            void SerializeEntities(YAML::Emitter& out, Entity parent_entity);
            void SerializeEntity(YAML::Emitter& out, Entity entity);
            void MapParentEntities();
            void DeserializeEntities(const YAML::Node& node, Entity parent_entity);
            void DeserializeEntity(const YAML::Node& node, Entity parent_entity, Entity entity);
    };
}