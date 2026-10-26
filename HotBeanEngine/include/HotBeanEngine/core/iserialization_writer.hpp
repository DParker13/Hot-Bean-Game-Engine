/**
 * @file iserialization_writer.hpp
 * @author Daniel Parker (DParker13)
 * @brief Abstract writer interface for serialization.
 * @version 0.1
 * @date 2026-06-19
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

#include <SDL3/SDL.h>
#include <glm/vec2.hpp>

namespace HBE::Core {
    struct ISerializationWriter {
        enum class FileWriteMode {
            Overwrite,
            Append,
        };

        virtual ~ISerializationWriter() = default;

        virtual void Write(const std::string &key, bool value) = 0;
        virtual void Write(const std::string &key, int value) = 0;
        virtual void Write(const std::string &key, float value) = 0;
        virtual void Write(const std::string &key, const std::string &value) = 0;
        virtual void Write(const std::string &key, uint8_t value) = 0;
        virtual void Write(const std::string &key, uint32_t value) = 0;
        virtual void Write(const std::string &key, int64_t value) = 0;
        virtual void Write(const std::string &key, glm::vec2 value) = 0;
        virtual void Write(const std::string &key, const SDL_Color &value) = 0;
        virtual void Write(const std::string &key, const std::filesystem::path &value) = 0;
        virtual void Write(const std::string &key, const std::vector<std::string> &value) = 0;
        virtual void Write(const std::string &key, const std::vector<std::filesystem::path> &value) = 0;

        /// @brief Begin a named section (e.g., a YAML map block). No-op for flat formats.
        virtual void BeginSection(const std::string &key) {}

        /// @brief Write an empty named section. No-op for formats without structured sections.
        virtual void WriteEmptySection(const std::string &key) {}

        /// @brief End the current section. No-op for flat formats.
        virtual void EndSection() {}

        /// @brief Write an inline comment. No-op for formats that don't support comments.
        virtual void WriteComment(const std::string &text) {}

        /// @brief Write buffered output to disk. Default implementation is unsupported.
        virtual void WriteToFile(const std::filesystem::path &filepath,
                                 FileWriteMode mode = FileWriteMode::Overwrite) const {}

        template <typename EnumT>
        void WriteEnum(const std::string &key, EnumT value) {
            Write(key, static_cast<int>(value));
        }
    };
} // namespace HBE::Core
