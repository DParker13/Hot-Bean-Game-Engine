/**
 * @file signature.hpp
 * @author Daniel Parker (DParker13)
 * @brief Used to identify which components an entity has.
 * @version 0.1
 * @date 2025-02-23
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <bitset>

#include <HotBeanEngine/core/config.hpp>

namespace HBE::Core {
    // Bitset indicates which components an entity has
    using Signature = std::bitset<MAX_COMPONENTS>;
} // namespace HBE::Core