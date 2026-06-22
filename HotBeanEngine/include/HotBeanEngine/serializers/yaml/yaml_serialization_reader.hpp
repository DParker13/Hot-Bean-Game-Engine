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

        bool ReadBool(std::string_view key) const override;
        int ReadInt(std::string_view key) const override;
        float ReadFloat(std::string_view key) const override;
        std::string ReadString(std::string_view key) const override;
        uint8_t ReadUint8(std::string_view key) const override;
        glm::vec2 ReadVec2(std::string_view key) const override;
        SDL_Color ReadColor(std::string_view key) const override;
    };
} // namespace HBE::Serializers
