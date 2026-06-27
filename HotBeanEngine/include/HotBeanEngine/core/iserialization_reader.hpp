/**
 * @file iserialization_reader.hpp
 * @author Daniel Parker (DParker13)
 * @brief Abstract reader interface for serialization.
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
    struct ISerializationReader {
        virtual ~ISerializationReader() = default;

        virtual bool Has(std::string_view key) const = 0;

        virtual void Read(std::string_view key, bool &value) const = 0;
        virtual void Read(std::string_view key, int &value) const = 0;
        virtual void Read(std::string_view key, float &value) const = 0;
        virtual void Read(std::string_view key, std::string &value) const = 0;
        virtual void Read(std::string_view key, uint8_t &value) const = 0;
        virtual void Read(std::string_view key, uint32_t &value) const = 0;
        virtual void Read(std::string_view key, int64_t &value) const = 0;
        virtual void Read(std::string_view key, glm::vec2 &value) const = 0;
        virtual void Read(std::string_view key, SDL_Color &value) const = 0;
        virtual void Read(std::string_view key, std::filesystem::path &value) const = 0;
        virtual void Read(std::string_view key, std::vector<std::string> &value) const = 0;
        virtual void Read(std::string_view key, std::vector<std::filesystem::path> &value) const = 0;
    };
} // namespace HBE::Core
