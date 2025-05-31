#pragma once

#include <bitset>

#include "config.hpp"

namespace Core::ECS {
    // Bitset indicates which components an entity has
    using Signature = std::bitset<Config::MAX_COMPONENTS>;
}