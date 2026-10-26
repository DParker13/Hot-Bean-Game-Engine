/**
 * @file yaml_entity_serializer.hpp
 * @author Daniel Parker (DParker13)
 * @brief Default entity serializer. Handles serialization and deserialization of entities using YAML format.
 * @version 0.1
 * @date 2025-10-17
 *
 * @copyright Copyright (c) 2025
 */

#include <HotBeanEngine/core/iserializable.hpp>
#include <HotBeanEngine/serializers/yaml/yaml_serialization_reader.hpp>
#include <HotBeanEngine/serializers/yaml/yaml_serialization_writer.hpp>

namespace HBE::Serializers {
    using Core::EntityID;

    /**
     * @brief Default entity serializer implementation using YAML
     */
    class YamlEntitySerializer : public Core::ISerializer {
    private:
        std::unordered_map<EntityID, std::vector<EntityID>> m_parent_entity_map;

    public:
        YamlEntitySerializer() = default;

        void Serialize(std::filesystem::path filepath, Core::ISerializable &object, bool append = false) override;
        void Deserialize(std::filesystem::path filepath, Core::ISerializable &object) override;

    private:
        void SerializeEntities(YamlWriter &writer, EntityID parent_entity);
        void SerializeEntity(YamlWriter &writer, EntityID entity);
        void MapParentEntities();
        void DeserializeEntities(const YamlReader &reader, EntityID parent_entity);
        void DeserializeEntity(const YamlReader &reader, EntityID parent_entity, EntityID entity);
    };
} // namespace HBE::Serializers