/**
 * @file yaml_scene_serializer.hpp
 * @author Daniel Parker (DParker13)
 * @brief Default scene serializer. Handles serialization and deserialization of scenes using YAML format.
 * @version 0.1
 * @date 2025-10-17
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <filesystem>

#include <HotBeanEngine/application/icomponent_factory.hpp>

namespace HBE::Serializers {
    using Application::IComponentFactory;
    using Core::EntityID;

    /**
     * @brief Default scene serializer implementation using YAML
     */
    class YamlSceneSerializer : public Core::ISerializer {
    private:
        std::unordered_map<EntityID, std::vector<EntityID>> m_parent_entity_map;
        std::shared_ptr<IComponentFactory> m_component_factory;

    public:
        DEFINE_NAME("YamlSceneSerializer");
        YamlSceneSerializer(std::shared_ptr<IComponentFactory> component_factory)
            : m_component_factory(component_factory) {}

        void Serialize(std::filesystem::path filepath) override;
        void Deserialize(std::filesystem::path filepath) override;

    private:
        void SerializeEntities(YAML::Emitter &out, EntityID parent_entity);
        void SerializeEntity(YAML::Emitter &out, EntityID entity);
        void MapParentEntities();
        void DeserializeEntities(const YAML::Node &node, EntityID parent_entity);
        void DeserializeEntity(const YAML::Node &node, EntityID parent_entity, EntityID entity);
    };
} // namespace HBE::Serializers