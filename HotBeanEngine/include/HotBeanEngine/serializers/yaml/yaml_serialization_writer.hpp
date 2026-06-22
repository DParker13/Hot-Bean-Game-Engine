/**
 * @file yaml_serialization_writer.hpp
 * @author Daniel Parker (DParker13)
 * @brief YAML-backed implementations of ISerializationWriter.
 * @version 0.1
 * @date 2026-06-19
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

#include <yaml-cpp/yaml.h>

#include <HotBeanEngine/core/iserialization_writer.hpp>

namespace HBE::Serializers {
    /// @brief Writes component data to a YAML::Emitter.
    class YamlComponentWriter : public Core::ISerializationWriter {
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
} // namespace HBE::Serializers
