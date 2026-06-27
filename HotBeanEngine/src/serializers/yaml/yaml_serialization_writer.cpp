/**
 * @file yaml_serialization_writer.cpp
 * @author Daniel Parker (DParker13)
 * @brief YAML-backed implementation of ISerializationWriter.
 * @version 0.1
 * @date 2026-06-19
 *
 * @copyright Copyright (c) 2026
 */

#include <HotBeanEngine/serializers/yaml/yaml_extensions.hpp>
#include <HotBeanEngine/serializers/yaml/yaml_serialization_writer.hpp>

namespace HBE::Serializers {
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

    void YamlComponentWriter::Write(std::string_view key, std::string value) {
        m_out << YAML::Key << key.data() << YAML::Value << value.data();
    }

    void YamlComponentWriter::Write(std::string_view key, uint8_t value) {
        m_out << YAML::Key << key.data() << YAML::Value << value;
    }

    void YamlComponentWriter::Write(std::string_view key, uint32_t value) {
        m_out << YAML::Key << key.data() << YAML::Value << value;
    }

    void YamlComponentWriter::Write(std::string_view key, int64_t value) {
        m_out << YAML::Key << key.data() << YAML::Value << value;
    }

    void YamlComponentWriter::Write(std::string_view key, glm::vec2 value) {
        m_out << YAML::Key << key.data() << YAML::Value << value;
    }

    void YamlComponentWriter::Write(std::string_view key, const SDL_Color &value) {
        m_out << YAML::Key << key.data() << YAML::Value << value;
    }

    void YamlComponentWriter::Write(std::string_view key, const std::filesystem::path &value) {
        m_out << YAML::Key << key.data() << YAML::Value << value.string();
    }

    void YamlComponentWriter::Write(std::string_view key, const std::vector<std::string> &value) {
        m_out << YAML::Key << key.data() << YAML::Value;
        m_out << YAML::BeginSeq << YAML::DoubleQuoted;
        for (const auto &item : value) {
            m_out << item;
        }
        m_out << YAML::EndSeq;
    }

    void YamlComponentWriter::Write(std::string_view key, const std::vector<std::filesystem::path> &value) {
        m_out << YAML::Key << key.data() << YAML::Value;
        m_out << YAML::BeginSeq << YAML::DoubleQuoted;
        for (const auto &item : value) {
            m_out << item.string();
        }
        m_out << YAML::EndSeq;
    }
} // namespace HBE::Serializers
