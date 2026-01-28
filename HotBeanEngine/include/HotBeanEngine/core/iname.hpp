/**
 * @file iname.hpp
 * @author Daniel Parker (DParker13)
 * @brief Interface for named objects.
 * @version 0.1
 * @date 2025-03-25
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <string_view>

#define DEFINE_NAME(Name)                                                                                              \
    static std::string_view StaticGetName() { return Name; }                                                           \
                                                                                                                       \
    std::string_view GetName() const { return Name; }

namespace HBE::Core {
    /// @brief Interface for named objects.
    struct IName {
        virtual std::string_view GetName() const = 0;
    };
} // namespace HBE::Core