/**
 * @file binary_format_constants.hpp
 * @author Daniel Parker (DParker13)
 * @brief Format constants for binary serialization formats.
 * @version 0.1
 * @date 2026-07-27
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

#include <cstdint>

namespace HBE::Serializers {

    namespace FormatBinary {
        inline constexpr char MAGIC[4] = {'H', 'B', 'E', 'F'};
        inline constexpr uint32_t VERSION = 1;
    } // namespace FormatBinary

} // namespace HBE::Serializers
