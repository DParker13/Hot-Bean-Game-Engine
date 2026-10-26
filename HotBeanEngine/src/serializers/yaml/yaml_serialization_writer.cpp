/**
 * @file yaml_serialization_writer.cpp
 * @author Daniel Parker (DParker13)
 * @brief YAML-backed implementation of ISerializationWriter.
 * @version 0.1
 * @date 2026-06-19
 *
 * @copyright Copyright (c) 2026
 */

#include <fstream>

#include <HotBeanEngine/serializers/yaml/yaml_extensions.hpp>
#include <HotBeanEngine/serializers/yaml/yaml_serialization_writer.hpp>

namespace HBE::Serializers {
    void YamlWriter::WriteToFile(const std::filesystem::path &filepath,
                                 Core::ISerializationWriter::FileWriteMode mode) const {
        const bool append = mode == Core::ISerializationWriter::FileWriteMode::Append;
        const bool has_existing_content =
            append && std::filesystem::exists(filepath) && std::filesystem::file_size(filepath) > 0;
        std::ios::openmode open_mode = std::ios::out;
        open_mode |= append ? std::ios::app : std::ios::trunc;

        std::ofstream file{filepath, open_mode};
        if (!file) {
            return;
        }
        if (has_existing_content) {
            file << '\n';
        }
        file << m_out.c_str();
    }

    void YamlWriter::Write(const std::string &key, bool value) { m_out << YAML::Key << key << YAML::Value << value; }

    void YamlWriter::Write(const std::string &key, int value) { m_out << YAML::Key << key << YAML::Value << value; }

    void YamlWriter::Write(const std::string &key, float value) { m_out << YAML::Key << key << YAML::Value << value; }

    void YamlWriter::Write(const std::string &key, const std::string &value) {
        m_out << YAML::Key << key << YAML::Value << YAML::DoubleQuoted << value;
    }

    void YamlWriter::Write(const std::string &key, uint8_t value) { m_out << YAML::Key << key << YAML::Value << value; }

    void YamlWriter::Write(const std::string &key, uint32_t value) {
        m_out << YAML::Key << key << YAML::Value << value;
    }

    void YamlWriter::Write(const std::string &key, int64_t value) { m_out << YAML::Key << key << YAML::Value << value; }

    void YamlWriter::Write(const std::string &key, glm::vec2 value) {
        m_out << YAML::Key << key << YAML::Value << value;
    }

    void YamlWriter::Write(const std::string &key, const SDL_Color &value) {
        m_out << YAML::Key << key << YAML::Value << value;
    }

    void YamlWriter::Write(const std::string &key, const std::filesystem::path &value) {
        m_out << YAML::Key << key << YAML::Value << YAML::DoubleQuoted << value.string();
    }

    void YamlWriter::Write(const std::string &key, const std::vector<std::string> &value) {
        m_out << YAML::Key << key << YAML::Value;
        m_out << YAML::BeginSeq << YAML::DoubleQuoted;
        for (const auto &item : value) {
            m_out << item;
        }
        m_out << YAML::EndSeq;
    }

    void YamlWriter::Write(const std::string &key, const std::vector<std::filesystem::path> &value) {
        m_out << YAML::Key << key << YAML::Value;
        m_out << YAML::BeginSeq << YAML::DoubleQuoted;
        for (const auto &item : value) {
            m_out << item.string();
        }
        m_out << YAML::EndSeq;
    }

    void YamlWriter::BeginSection(const std::string &key) {
        m_out << YAML::Key << key << YAML::Value << YAML::BeginMap;
    }

    void YamlWriter::WriteEmptySection(const std::string &key) {
        m_out << YAML::Key << key << YAML::Value << YAML::Null;
    }

    void YamlWriter::EndSection() { m_out << YAML::EndMap; }

    void YamlWriter::WriteComment(const std::string &text) { m_out << YAML::Comment(text); }
} // namespace HBE::Serializers
