/**
 * @file yaml_serialization_reader.hpp
 * @author Daniel Parker (DParker13)
 * @brief YAML-backed implementations of ISerializationReader.
 * @version 0.1
 * @date 2026-06-19
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

#include <yaml-cpp/yaml.h>

#include <HotBeanEngine/core/iserialization_reader.hpp>

namespace HBE::Serializers {
    /// @brief Reads component data from a YAML::Node.
    class YamlComponentReader : public Core::ISerializationReader {
    private:
        const YAML::Node &m_node;

    public:
        explicit YamlComponentReader(const YAML::Node &node) : m_node(node) {}

        bool Has(std::string_view key) const override;

        void Read(std::string_view key, bool &value) const override;
        void Read(std::string_view key, int &value) const override;
        void Read(std::string_view key, float &value) const override;
        void Read(std::string_view key, std::string &value) const override;
        void Read(std::string_view key, uint8_t &value) const override;
        void Read(std::string_view key, uint32_t &value) const override;
        void Read(std::string_view key, int64_t &value) const override;
        void Read(std::string_view key, glm::vec2 &value) const override;
        void Read(std::string_view key, SDL_Color &value) const override;
        void Read(std::string_view key, std::filesystem::path &value) const override;
        void Read(std::string_view key, std::vector<std::string> &value) const override;
        void Read(std::string_view key, std::vector<std::filesystem::path> &value) const override;
    };
} // namespace HBE::Serializers
