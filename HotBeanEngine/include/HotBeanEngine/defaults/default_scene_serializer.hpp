/**
 * @file default_scene_serializer.hpp
 * @author Daniel Parker (DParker13)
 * @brief Default scene serializer. Handles serialization and deserialization of scenes using YAML format.
 * @version 0.1
 * @date 2025-10-17
 * 
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <fstream>
#include <filesystem>

#include <HotBeanEngine/defaults/components/default_component_factory.hpp>

using namespace HBE::Default::Components;

namespace HBE::Default {

    /**
     * @brief Default scene serializer implementation using YAML
     */
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