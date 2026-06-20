/**
 * @file yaml_component_serializer.cpp
 * @author Daniel Parker (DParker13)
 * @brief YAML-backed implementations of IComponentWriter and IComponentReader.
 * @version 0.1
 * @date 2026-06-19
 *
 * @copyright Copyright (c) 2026
 */

#include <HotBeanEngine/serializers/yaml/yaml_component_serializer.hpp>
#include <HotBeanEngine/serializers/yaml/yaml_extensions.hpp>

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

    //----------------------------------------------------------------
    // YamlComponentReader
    //----------------------------------------------------------------

    bool YamlComponentReader::Has(std::string_view key) const { return m_node[key.data()].IsDefined(); }

    bool YamlComponentReader::ReadBool(std::string_view key) const { return m_node[key.data()].as<bool>(); }
    int YamlComponentReader::ReadInt(std::string_view key) const { return m_node[key.data()].as<int>(); }
    float YamlComponentReader::ReadFloat(std::string_view key) const { return m_node[key.data()].as<float>(); }
    std::string YamlComponentReader::ReadString(std::string_view key) const {
        return m_node[key.data()].as<std::string>();
    }
    uint8_t YamlComponentReader::ReadUint8(std::string_view key) const {
        return static_cast<uint8_t>(m_node[key.data()].as<int>());
    }
    glm::vec2 YamlComponentReader::ReadVec2(std::string_view key) const { return m_node[key.data()].as<glm::vec2>(); }
    SDL_Color YamlComponentReader::ReadColor(std::string_view key) const { return m_node[key.data()].as<SDL_Color>(); }
} // namespace HBE::Serializers
