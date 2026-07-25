/**
 * @file binary_serialization_writer.hpp
 * @author Daniel Parker (DParker13)
 * @brief Binary-backed implementation of ISerializationWriter.
 * Collects component fields in memory; BinarySceneSerializer flushes them to the stream.
 * @version 0.1
 * @date 2026-07-24
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

#include <vector>

#include <HotBeanEngine/core/iserialization_writer.hpp>
#include <HotBeanEngine/serializers/binary/binary_serialization_types.hpp>

namespace HBE::Serializers {

    /// @brief Buffers component field writes for later binary serialization.
    class BinaryComponentWriter : public Core::ISerializationWriter {
    public:
        std::vector<BinaryField> m_fields;

        void Write(std::string_view key, bool value) override;
        void Write(std::string_view key, int value) override;
        void Write(std::string_view key, float value) override;
        void Write(std::string_view key, std::string_view value) override;
        void Write(std::string_view key, std::string value) override;
        void Write(std::string_view key, uint8_t value) override;
        void Write(std::string_view key, uint32_t value) override;
        void Write(std::string_view key, int64_t value) override;
        void Write(std::string_view key, glm::vec2 value) override;
        void Write(std::string_view key, const SDL_Color &value) override;
        void Write(std::string_view key, const std::filesystem::path &value) override;
        void Write(std::string_view key, const std::vector<std::string> &value) override;
        void Write(std::string_view key, const std::vector<std::filesystem::path> &value) override;
    };

} // namespace HBE::Serializers
