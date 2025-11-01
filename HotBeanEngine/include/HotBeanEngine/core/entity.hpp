/**
 * @file entity.hpp
 * @author Daniel Parker (DParker13)
 * @brief Defines the EntityID type used in the ECS architecture.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <SDL3/SDL.h>

namespace HBE::Core {
    // EntityID is a unsigned 64-bit integer
    // This is used to identify an entity
    using EntityID = Uint64;
}