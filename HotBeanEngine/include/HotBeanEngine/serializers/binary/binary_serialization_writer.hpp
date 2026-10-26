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
    class BinaryWriter : public Core::ISerializationWriter {
    public:
        std::vector<BinaryField> m_fields;

        void Write(const std::string &key, bool value) override;
        void Write(const std::string &key, int value) override;
        void Write(const std::string &key, float value) override;
        void Write(const std::string &key, const std::string &value) override;
        void Write(const std::string &key, uint8_t value) override;
        void Write(const std::string &key, uint32_t value) override;
        void Write(const std::string &key, int64_t value) override;
        void Write(const std::string &key, glm::vec2 value) override;
        void Write(const std::string &key, const SDL_Color &value) override;
        void Write(const std::string &key, const std::filesystem::path &value) override;
        void Write(const std::string &key, const std::vector<std::string> &value) override;
        void Write(const std::string &key, const std::vector<std::filesystem::path> &value) override;

        void WriteToFile(const std::filesystem::path &filepath,
                         Core::ISerializationWriter::FileWriteMode mode =
                             Core::ISerializationWriter::FileWriteMode::Overwrite) const override {}
    };

} // namespace HBE::Serializers
