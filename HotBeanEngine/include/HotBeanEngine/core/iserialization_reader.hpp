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
#include <string>
#include <string_view>

#include <SDL3/SDL.h>
#include <glm/vec2.hpp>

namespace HBE::Core {
    struct ISerializationReader {
        virtual ~ISerializationReader() = default;

        virtual bool Has(std::string_view key) const = 0;

        virtual bool ReadBool(std::string_view key) const = 0;
        virtual int ReadInt(std::string_view key) const = 0;
        virtual float ReadFloat(std::string_view key) const = 0;
        virtual std::string ReadString(std::string_view key) const = 0;
        virtual uint8_t ReadUint8(std::string_view key) const = 0;
        virtual glm::vec2 ReadVec2(std::string_view key) const = 0;
        virtual SDL_Color ReadColor(std::string_view key) const = 0;
    };
} // namespace HBE::Core
