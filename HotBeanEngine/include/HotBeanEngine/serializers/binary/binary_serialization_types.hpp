/**
 * @file binary_serialization_types.hpp
 * @author Daniel Parker (DParker13)
 * @brief Shared field types for binary serialization.
 * @version 0.1
 * @date 2026-07-24
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

#include <cstdint>
#include <filesystem>
#include <string>
#include <variant>
#include <vector>

#include <SDL3/SDL.h>
#include <glm/vec2.hpp>

namespace HBE::Serializers {

    /// @brief Type tag written to the binary stream to identify each field value.
    enum class FieldType : uint8_t {
        Bool = 0,
        Int = 1,
        Float = 2,
        String = 3,
        Uint8 = 4,
        Uint32 = 5,
        Int64 = 6,
        Vec2 = 7,
        Color = 8,
        Path = 9,
        VecString = 10,
        VecPath = 11,
    };

    using FieldValue = std::variant<bool,                              // FieldType::Bool
                                    int,                               // FieldType::Int
                                    float,                             // FieldType::Float
                                    std::string,                       // FieldType::String
                                    uint8_t,                           // FieldType::Uint8
                                    uint32_t,                          // FieldType::Uint32
                                    int64_t,                           // FieldType::Int64
                                    glm::vec2,                         // FieldType::Vec2
                                    SDL_Color,                         // FieldType::Color
                                    std::filesystem::path,             // FieldType::Path
                                    std::vector<std::string>,          // FieldType::VecString
                                    std::vector<std::filesystem::path> // FieldType::VecPath
                                    >;

    struct BinaryField {
        std::string key;
        FieldType type;
        FieldValue value;
    };

} // namespace HBE::Serializers
