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

#include <vector>

#include <yaml-cpp/yaml.h>

#include <HotBeanEngine/core/iserialization_reader.hpp>

namespace HBE::Serializers {
    /// @brief Reads component data from a YAML::Node.
    class YamlReader : public Core::ISerializationReader {
    private:
        YAML::Node m_node;
        std::vector<YAML::Node> m_stack;
        std::filesystem::path m_source_path;

    public:
        explicit YamlReader(const YAML::Node &node, std::filesystem::path source_path = {})
            : m_node(node), m_source_path(std::move(source_path)) {}

        YamlReader operator[](std::string_view key) const {
            return YamlReader(m_node[std::string(key)], m_source_path);
        }
        YamlReader operator[](size_t index) const { return YamlReader(m_node[index], m_source_path); }

        auto begin() const { return m_node.begin(); }
        auto end() const { return m_node.end(); }

        void BeginSection(std::string_view key) override;
        void EndSection() override;

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
        size_t Size() const override;

        std::filesystem::path GetSourcePath() const override { return m_source_path; }
    };
} // namespace HBE::Serializers
