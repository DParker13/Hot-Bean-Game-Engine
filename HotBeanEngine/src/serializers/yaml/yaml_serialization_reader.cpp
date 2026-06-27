/**
 * @file yaml_component_serializer.cpp
 * @author Daniel Parker (DParker13)
 * @brief YAML-backed implementations of ISerializationReader.
 * @version 0.1
 * @date 2026-06-19
 *
 * @copyright Copyright (c) 2026
 */

#include <HotBeanEngine/serializers/yaml/yaml_extensions.hpp>
#include <HotBeanEngine/serializers/yaml/yaml_serialization_reader.hpp>

namespace HBE::Serializers {
    bool YamlComponentReader::Has(std::string_view key) const { return m_node[key.data()].IsDefined(); }

    void YamlComponentReader::Read(std::string_view key, bool &value) const {
        if (Has(key)) {
            value = m_node[key.data()].as<bool>();
        }
    }
    void YamlComponentReader::Read(std::string_view key, int &value) const {
        if (Has(key)) {
            value = m_node[key.data()].as<int>();
        }
    }
    void YamlComponentReader::Read(std::string_view key, float &value) const {
        if (Has(key)) {
            value = m_node[key.data()].as<float>();
        }
    }
    void YamlComponentReader::Read(std::string_view key, std::string &value) const {
        if (Has(key)) {
            value = m_node[key.data()].as<std::string>();
        }
    }
    void YamlComponentReader::Read(std::string_view key, uint8_t &value) const {
        if (Has(key)) {
            value = static_cast<uint8_t>(m_node[key.data()].as<int>());
        }
    }
    void YamlComponentReader::Read(std::string_view key, uint32_t &value) const {
        if (Has(key)) {
            value = m_node[key.data()].as<uint32_t>();
        }
    }
    void YamlComponentReader::Read(std::string_view key, int64_t &value) const {
        if (Has(key)) {
            value = static_cast<int64_t>(m_node[key.data()].as<int>());
        }
    }
    void YamlComponentReader::Read(std::string_view key, glm::vec2 &value) const {
        if (Has(key)) {
            value = m_node[key.data()].as<glm::vec2>();
        }
    }
    void YamlComponentReader::Read(std::string_view key, SDL_Color &value) const {
        if (Has(key)) {
            value = m_node[key.data()].as<SDL_Color>();
        }
    }
    void YamlComponentReader::Read(std::string_view key, std::filesystem::path &value) const {
        if (Has(key)) {
            value = m_node[key.data()].as<std::filesystem::path>();
        }
    }
    void YamlComponentReader::Read(std::string_view key, std::vector<std::string> &value) const {
        if (!Has(key)) {
            return;
        }

        const YAML::Node &arrayNode = m_node[key.data()];
        if (!arrayNode.IsSequence()) {
            return;
        }
        value.clear();
        for (const auto &item : arrayNode) {
            value.push_back(item.as<std::string>());
        }
    }

    void YamlComponentReader::Read(std::string_view key, std::vector<std::filesystem::path> &value) const {
        if (!Has(key)) {
            return;
        }

        const YAML::Node &arrayNode = m_node[key.data()];
        if (!arrayNode.IsSequence()) {
            return;
        }
        value.clear();
        for (const auto &item : arrayNode) {
            value.push_back(std::filesystem::path(item.as<std::string>()));
        }
    }

} // namespace HBE::Serializers
