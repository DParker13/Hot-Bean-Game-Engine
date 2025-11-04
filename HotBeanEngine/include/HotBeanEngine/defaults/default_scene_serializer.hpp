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

#include <filesystem>

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/defaults/components/default_components.hpp>

namespace HBE::Default {
    using namespace HBE::Application;
    using namespace HBE::Default::Components;

    /**
     * @brief Default scene serializer implementation using YAML
     */
    class DefaultSceneSerializer : public ISerializer {
    private:
        std::unordered_map<EntityID, std::vector<EntityID>> m_parent_entity_map;
        std::shared_ptr<IComponentFactory> m_component_factory;

    public:
        DefaultSceneSerializer(std::shared_ptr<IComponentFactory> component_factory);

        void Serialize(std::string_view filepath) override;
        void Deserialize(std::string_view filepath) override;
        bool FileExists(std::string_view filepath) override;

    private:
        void SerializeEntities(YAML::Emitter& out, EntityID parent_entity);
        void SerializeEntity(YAML::Emitter& out, EntityID entity);
        void MapParentEntities();
        void DeserializeEntities(const YAML::Node& node, EntityID parent_entity);
        void DeserializeEntity(const YAML::Node& node, EntityID parent_entity, EntityID entity);
    };
}