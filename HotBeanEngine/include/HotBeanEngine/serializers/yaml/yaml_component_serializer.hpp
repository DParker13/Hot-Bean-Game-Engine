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
#include <HotBeanEngine/serializers/yaml/yaml_extensions.hpp>

namespace HBE::Serializers {
    /// @brief Writes component data to a YAML::Emitter.
    class YamlComponentWriter : public Core::IComponentWriter {
    public:
        explicit YamlComponentWriter(YAML::Emitter &out) : m_out(out) {}

        void Write(std::string_view key, bool value) override {
            m_out << YAML::Key << key.data() << YAML::Value << value;
        }
        void Write(std::string_view key, int value) override {
            m_out << YAML::Key << key.data() << YAML::Value << value;
        }
        void Write(std::string_view key, float value) override {
            m_out << YAML::Key << key.data() << YAML::Value << value;
        }
        void Write(std::string_view key, std::string_view value) override {
            m_out << YAML::Key << key.data() << YAML::Value << value.data();
        }
        void Write(std::string_view key, uint8_t value) override {
            m_out << YAML::Key << key.data() << YAML::Value << static_cast<int>(value);
        }
        void Write(std::string_view key, glm::vec2 value) override {
            m_out << YAML::Key << key.data() << YAML::Value << value;
        }
        void Write(std::string_view key, SDL_Color value) override {
            m_out << YAML::Key << key.data() << YAML::Value << value;
        }

    private:
        YAML::Emitter &m_out;
    };

    /// @brief Reads component data from a YAML::Node.
    class YamlComponentReader : public Core::IComponentReader {
    public:
        explicit YamlComponentReader(const YAML::Node &node) : m_node(node) {}

        bool Has(std::string_view key) const override { return m_node[key.data()].IsDefined(); }

        bool ReadBool(std::string_view key) const override { return m_node[key.data()].as<bool>(); }
        int ReadInt(std::string_view key) const override { return m_node[key.data()].as<int>(); }
        float ReadFloat(std::string_view key) const override { return m_node[key.data()].as<float>(); }
        std::string ReadString(std::string_view key) const override { return m_node[key.data()].as<std::string>(); }
        uint8_t ReadUint8(std::string_view key) const override {
            return static_cast<uint8_t>(m_node[key.data()].as<int>());
        }
        glm::vec2 ReadVec2(std::string_view key) const override { return m_node[key.data()].as<glm::vec2>(); }
        SDL_Color ReadColor(std::string_view key) const override { return m_node[key.data()].as<SDL_Color>(); }

    private:
        const YAML::Node &m_node;
    };
} // namespace HBE::Serializers
