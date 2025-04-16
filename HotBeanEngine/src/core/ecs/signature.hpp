#pragma once

#include <bitset>

#include "component.hpp"

namespace Core {
    namespace ECS {
        // Bitset indicates which components an entity has
        using Signature = std::bitset<MAX_COMPONENTS>;
    }
}