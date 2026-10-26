/**
 * @file binary_serialization_reader.hpp
 * @author Daniel Parker (DParker13)
 * @brief Binary-backed implementation of ISerializationReader.
 * @version 0.1
 * @date 2026-07-24
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

#include <functional>
#include <string_view>
#include <unordered_map>
#include <vector>

#include <HotBeanEngine/core/iserialization_reader.hpp>
#include <HotBeanEngine/serializers/binary/binary_serialization_types.hpp>

namespace HBE::Serializers {

    /// @brief Reads fields from a pre-loaded binary field map.
    class BinaryReader : public Core::ISerializationReader {
        struct KeyHash {
            using is_transparent = void;

            size_t operator()(std::string_view key) const noexcept { return std::hash<std::string_view>{}(key); }
        };

        std::unordered_map<std::string, BinaryField, KeyHash, std::equal_to<>> m_fields;
        std::filesystem::path m_source_path;

    public:
        explicit BinaryReader(std::vector<BinaryField> fields, std::filesystem::path source_path = {});

        bool Has(std::string_view key) const override;
        size_t Size() const override;

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

        std::filesystem::path GetSourcePath() const override { return m_source_path; }
    };

} // namespace HBE::Serializers
