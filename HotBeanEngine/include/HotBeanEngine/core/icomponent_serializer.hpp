/**
 * @file icomponent_serializer.hpp
 * @author Daniel Parker (DParker13)
 * @brief Abstract reader/writer interfaces for component serialization.
 * Components use these instead of YAML types directly, keeping them
 * format-agnostic.
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
    /// @brief Abstract write interface used by IComponent::Serialize.
    struct IComponentWriter {
        virtual ~IComponentWriter() = default;

        virtual void Write(std::string_view key, bool value) = 0;
        virtual void Write(std::string_view key, int value) = 0;
        virtual void Write(std::string_view key, float value) = 0;
        virtual void Write(std::string_view key, std::string_view value) = 0;
        virtual void Write(std::string_view key, uint8_t value) = 0;
        virtual void Write(std::string_view key, glm::vec2 value) = 0;
        virtual void Write(std::string_view key, SDL_Color value) = 0;
    };

    /// @brief Abstract read interface used by IComponent::Deserialize.
    struct IComponentReader {
        virtual ~IComponentReader() = default;

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
