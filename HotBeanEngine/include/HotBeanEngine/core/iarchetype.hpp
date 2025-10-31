/**
 * @file iarchetype.hpp
 * @author Daniel Parker (DParker13)
 * @brief Interface for archetypes.
 * @version 0.1
 * @date 2025-07-10
 * 
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <vector>
#include <string>

namespace HBE::Core {
    /// @brief Interface for archetypes.
    struct IArchetype {
        virtual std::vector<std::string> GetComponentNames() = 0;
    };
}