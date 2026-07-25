/**
 * @file binary_scene_serializer.hpp
 * @author Daniel Parker (DParker13)
 * @brief Serializes and deserializes scenes to/from a compact binary format (.hbs).
 *
 * Binary format (little-endian):
 *   [4]     magic "HBSC"
 *   [4]     version uint32
 *   [4+N]   scene name string
 *   [4]     root entity count
 *   Per entity (recursive):
 *     [4]     component count
 *     Per component:
 *       [4+N]   component name
 *       [4]     field count
 *       Per field:
 *         [4+N]   key
 *         [1]     type tag (FieldType)
 *         [N]     value (varies by type)
 *     [4]     child entity count
 *     ... child entities
 *
 * @version 0.1
 * @date 2026-07-24
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

#include <filesystem>
#include <unordered_map>
#include <vector>

#include <HotBeanEngine/core/entity.hpp>
#include <HotBeanEngine/core/iserializer.hpp>
#include <HotBeanEngine/factories/icomponent_factory.hpp>

namespace HBE::Serializers {

    class BinarySceneSerializer : public Core::ISerializer {
    private:
        std::shared_ptr<Factories::IComponentFactory> m_component_factory;
        std::unordered_map<Core::EntityID, std::vector<Core::EntityID>> m_parent_entity_map;

    public:
        DEFINE_NAME("BinarySceneSerializer");

        explicit BinarySceneSerializer(std::shared_ptr<Factories::IComponentFactory> component_factory)
            : m_component_factory(component_factory) {}

        void Serialize(std::filesystem::path filepath) override;
        void Deserialize(std::filesystem::path filepath) override;

    private:
        void MapParentEntities();
        void WriteEntities(std::ostream &out, Core::EntityID parent_entity);
        void WriteEntity(std::ostream &out, Core::EntityID entity);
        void ReadEntities(std::istream &in, Core::EntityID parent_entity, uint32_t count);
        void ReadEntity(std::istream &in, Core::EntityID parent_entity);
    };

} // namespace HBE::Serializers
