/**
 * @file yaml_component_serializer.hpp
 * @author Daniel Parker (DParker13)
 * @brief YAML-backed implementations of IComponentWriter and IComponentReader.
 * @version 0.1
 * @date 2026-06-19
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

#include <yaml-cpp/yaml.h>

#include <HotBeanEngine/core/icomponent_serializer.hpp>

namespace HBE::Serializers {
    /// @brief Writes component data to a YAML::Emitter.
    class YamlComponentWriter : public Core::IComponentWriter {
    private:
        YAML::Emitter &m_out;

    public:
        explicit YamlComponentWriter(YAML::Emitter &out) : m_out(out) {}

        void Write(std::string_view key, bool value) override;
        void Write(std::string_view key, int value) override;
        void Write(std::string_view key, float value) override;
        void Write(std::string_view key, std::string_view value) override;
        void Write(std::string_view key, uint8_t value) override;
        void Write(std::string_view key, glm::vec2 value) override;
        void Write(std::string_view key, SDL_Color value) override;
    };

    /// @brief Reads component data from a YAML::Node.
    class YamlComponentReader : public Core::IComponentReader {
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
