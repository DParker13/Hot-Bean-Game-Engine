/**
 * @file yaml_serializer.hpp
 * @author Daniel Parker (DParker13)
 * @brief Default serializer. Handles serialization and deserialization of objects using YAML format.
 * @version 0.1
 * @date 2025-10-17
 *
 * @copyright Copyright (c) 2025
 */

#include <HotBeanEngine/core/iserializable.hpp>
#include <HotBeanEngine/serializers/yaml/yaml_serialization_reader.hpp>
#include <HotBeanEngine/serializers/yaml/yaml_serialization_writer.hpp>

#include <HotBeanEngine/factories/icomponent_factory.hpp>

namespace HBE::Serializers {
    /**
     * @brief Default scene serializer implementation using YAML
     */
    class YamlSerializer : public Core::ISerializer {
    public:
        YamlSerializer() = default;

        void Serialize(std::filesystem::path filepath, Core::ISerializable &object, bool append = false) override;
        void Deserialize(std::filesystem::path filepath, Core::ISerializable &object) override;
    };
} // namespace HBE::Serializers