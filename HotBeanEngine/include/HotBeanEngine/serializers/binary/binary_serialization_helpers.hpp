/**
 * @file binary_serialization_helpers.hpp
 * @author Daniel Parker (DParker13)
 * @brief Shared helper functions for binary serialization read/write operations.
 * @version 0.1
 * @date 2026-07-27
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

#include <istream>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>

#include <SDL3/SDL.h>
#include <glm/glm.hpp>

#include <HotBeanEngine/serializers/binary/binary_serialization_types.hpp>

namespace HBE::Serializers {

    // ---- Write helpers ----

    /// @brief Writes a trivial type to the output stream
    template <typename T>
    inline void WriteT(std::ostream &out, T val) {
        out.write(reinterpret_cast<const char *>(&val), sizeof(T));
    }

    /// @brief Writes a string with length prefix to the output stream
    inline void WriteStr(std::ostream &out, std::string_view s) {
        WriteT<uint32_t>(out, static_cast<uint32_t>(s.size()));
        out.write(s.data(), static_cast<std::streamsize>(s.size()));
    }

    /// @brief Writes a BinaryField to the output stream
    inline void WriteField(std::ostream &out, const BinaryField &f) {
        WriteStr(out, f.key);
        WriteT<uint8_t>(out, static_cast<uint8_t>(f.type));
        std::visit(
            [&](auto &&val) {
                using T = std::decay_t<decltype(val)>;
                if constexpr (std::is_same_v<T, bool>)
                    WriteT<uint8_t>(out, val ? uint8_t{1} : uint8_t{0});
                else if constexpr (std::is_same_v<T, int>)
                    WriteT<int32_t>(out, static_cast<int32_t>(val));
                else if constexpr (std::is_same_v<T, float>)
                    WriteT<float>(out, val);
                else if constexpr (std::is_same_v<T, std::string>)
                    WriteStr(out, val);
                else if constexpr (std::is_same_v<T, uint8_t>)
                    WriteT<uint8_t>(out, val);
                else if constexpr (std::is_same_v<T, uint32_t>)
                    WriteT<uint32_t>(out, val);
                else if constexpr (std::is_same_v<T, int64_t>)
                    WriteT<int64_t>(out, val);
                else if constexpr (std::is_same_v<T, glm::vec2>) {
                    WriteT<float>(out, val.x);
                    WriteT<float>(out, val.y);
                }
                else if constexpr (std::is_same_v<T, SDL_Color>) {
                    WriteT<uint8_t>(out, val.r);
                    WriteT<uint8_t>(out, val.g);
                    WriteT<uint8_t>(out, val.b);
                    WriteT<uint8_t>(out, val.a);
                }
                else if constexpr (std::is_same_v<T, std::filesystem::path>)
                    WriteStr(out, val.string());
                else if constexpr (std::is_same_v<T, std::vector<std::string>>) {
                    WriteT<uint32_t>(out, static_cast<uint32_t>(val.size()));
                    for (const auto &s : val)
                        WriteStr(out, s);
                }
                else if constexpr (std::is_same_v<T, std::vector<std::filesystem::path>>) {
                    WriteT<uint32_t>(out, static_cast<uint32_t>(val.size()));
                    for (const auto &p : val)
                        WriteStr(out, p.string());
                }
            },
            f.value);
    }

    // ---- Read helpers ----

    /// @brief Reads a trivial type from the input stream
    template <typename T>
    inline T ReadT(std::istream &in) {
        T val{};
        in.read(reinterpret_cast<char *>(&val), sizeof(T));
        return val;
    }

    /// @brief Reads a string with length prefix from the input stream
    inline std::string ReadStr(std::istream &in) {
        uint32_t len = ReadT<uint32_t>(in);
        std::string s(len, '\0');
        in.read(s.data(), static_cast<std::streamsize>(len));
        return s;
    }

    /// @brief Reads a BinaryField from the input stream
    inline BinaryField ReadField(std::istream &in) {
        BinaryField f;
        f.key = ReadStr(in);
        f.type = static_cast<FieldType>(ReadT<uint8_t>(in));

        switch (f.type) {
        case FieldType::Bool:
            f.value = static_cast<bool>(ReadT<uint8_t>(in));
            break;
        case FieldType::Int:
            f.value = static_cast<int>(ReadT<int32_t>(in));
            break;
        case FieldType::Float:
            f.value = ReadT<float>(in);
            break;
        case FieldType::String:
            f.value = ReadStr(in);
            break;
        case FieldType::Uint8:
            f.value = ReadT<uint8_t>(in);
            break;
        case FieldType::Uint32:
            f.value = ReadT<uint32_t>(in);
            break;
        case FieldType::Int64:
            f.value = ReadT<int64_t>(in);
            break;
        case FieldType::Vec2: {
            float x = ReadT<float>(in);
            float y = ReadT<float>(in);
            f.value = glm::vec2{x, y};
            break;
        }
        case FieldType::Color: {
            SDL_Color c{};
            c.r = ReadT<uint8_t>(in);
            c.g = ReadT<uint8_t>(in);
            c.b = ReadT<uint8_t>(in);
            c.a = ReadT<uint8_t>(in);
            f.value = c;
            break;
        }
        case FieldType::Path:
            f.value = std::filesystem::path(ReadStr(in));
            break;
        case FieldType::VecString: {
            uint32_t n = ReadT<uint32_t>(in);
            std::vector<std::string> v(n);
            for (auto &s : v)
                s = ReadStr(in);
            f.value = std::move(v);
            break;
        }
        case FieldType::VecPath: {
            uint32_t n = ReadT<uint32_t>(in);
            std::vector<std::filesystem::path> v(n);
            for (auto &p : v)
                p = std::filesystem::path(ReadStr(in));
            f.value = std::move(v);
            break;
        }
        }
        return f;
    }

} // namespace HBE::Serializers
