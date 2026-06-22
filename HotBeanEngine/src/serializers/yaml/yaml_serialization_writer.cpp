/**
 * @file yaml_component_serializer.cpp
 * @author Daniel Parker (DParker13)
 * @brief YAML-backed implementations of ISerializationWriter and ISerializationReader.
 * @version 0.1
 * @date 2026-06-19
 *
 * @copyright Copyright (c) 2026
 */

#include <HotBeanEngine/serializers/yaml/yaml_extensions.hpp>
#include <HotBeanEngine/serializers/yaml/yaml_serialization_writer.hpp>

namespace HBE::Serializers {
    //----------------------------------------------------------------
    // YamlComponentWriter
    //----------------------------------------------------------------

    void YamlComponentWriter::Write(std::string_view key, bool value) {
        m_out << YAML::Key << key.data() << YAML::Value << value;
    }
    void YamlComponentWriter::Write(std::string_view key, int value) {
        m_out << YAML::Key << key.data() << YAML::Value << value;
    }
    void YamlComponentWriter::Write(std::string_view key, float value) {
        m_out << YAML::Key << key.data() << YAML::Value << value;
    }
    void YamlComponentWriter::Write(std::string_view key, std::string_view value) {
        m_out << YAML::Key << key.data() << YAML::Value << value.data();
    }
    void YamlComponentWriter::Write(std::string_view key, uint8_t value) {
        m_out << YAML::Key << key.data() << YAML::Value << static_cast<int>(value);
    }
    void YamlComponentWriter::Write(std::string_view key, glm::vec2 value) {
        m_out << YAML::Key << key.data() << YAML::Value << value;
    }
    void YamlComponentWriter::Write(std::string_view key, SDL_Color value) {
        m_out << YAML::Key << key.data() << YAML::Value << value;
    }
} // namespace HBE::Serializers
