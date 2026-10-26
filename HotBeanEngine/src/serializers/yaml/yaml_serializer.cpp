/**
 * @file yaml_serializer.cpp
 * @author Daniel Parker (DParker13)
 * @brief YAML-backed implementation of the ISerializer interface.
 * @version 1.0
 * @date 2025-10-11
 *
 * @copyright Copyright (c) 2025
 */

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/serializers/yaml/yaml_serialization_reader.hpp>
#include <HotBeanEngine/serializers/yaml/yaml_serialization_writer.hpp>
#include <HotBeanEngine/serializers/yaml/yaml_serializer.hpp>

namespace HBE::Serializers {
    using namespace Core;

    void YamlSerializer::Serialize(std::filesystem::path filepath, Core::ISerializable &object, bool append) {
        assert(!filepath.empty() && "Current filepath is empty.");

        try {
            YAML::Emitter out;
            out.SetIndent(2);
            YamlWriter writer(out);

            out << YAML::BeginMap;
            object.Serialize(writer);
            out << YAML::EndMap;

            writer.WriteToFile(filepath, append ? ISerializationWriter::FileWriteMode::Append
                                                : ISerializationWriter::FileWriteMode::Overwrite);
        } catch (const std::exception &e) {
            LOG(Core::LoggingType::ERROR,
                "Failed to serialize YAML object: " + filepath.string() + " with error: " + e.what());
        } catch (...) {
            LOG(Core::LoggingType::ERROR, "Failed to serialize YAML object: " + filepath.string());
        }
    }

    void YamlSerializer::Deserialize(std::filesystem::path filepath, Core::ISerializable &object) {
        assert(!filepath.empty() && "Current filepath is empty.");

        try {
            // Parse the YAML data
            YAML::Node in = YAML::LoadFile(filepath.string());
            YamlReader reader(in, filepath);

            // Deserialize the object data into the provided object
            object.Deserialize(reader);
        } catch (const std::exception &e) {
            LOG(Core::LoggingType::ERROR,
                "Failed to deserialize YAML object: " + filepath.string() + " with error: " + e.what());
        } catch (...) {
            LOG(Core::LoggingType::ERROR, "Failed to deserialize YAML object: " + filepath.string());
        }
    }
} // namespace HBE::Serializers