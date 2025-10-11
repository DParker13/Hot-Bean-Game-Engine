#pragma once

#include <bitset>

#include <HotBeanEngine/core/config.hpp>

namespace HBE::Core {
    // Bitset indicates which components an entity has
    using Signature = std::bitset<Config::MAX_COMPONENTS>;
}