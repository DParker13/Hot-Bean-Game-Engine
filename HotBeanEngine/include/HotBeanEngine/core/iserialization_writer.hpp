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
#include <string_view>

#include <SDL3/SDL.h>
#include <glm/vec2.hpp>

namespace HBE::Core {
    struct ISerializationWriter {
        virtual ~ISerializationWriter() = default;

        virtual void Write(std::string_view key, bool value) = 0;
        virtual void Write(std::string_view key, int value) = 0;
        virtual void Write(std::string_view key, float value) = 0;
        virtual void Write(std::string_view key, std::string_view value) = 0;
        virtual void Write(std::string_view key, uint8_t value) = 0;
        virtual void Write(std::string_view key, glm::vec2 value) = 0;
        virtual void Write(std::string_view key, SDL_Color value) = 0;
    };
} // namespace HBE::Core
