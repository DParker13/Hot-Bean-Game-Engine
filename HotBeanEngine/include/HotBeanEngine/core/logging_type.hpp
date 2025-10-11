/**
 * @file logging_type.hpp
 * @author Daniel Parker (DParker13)
 * @brief Used for setting the logging level.
 * @version 0.1
 * @date 2025-03-27
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

namespace HBE::Core {
    /// @brief Used for setting the logging level.
    enum class LoggingType {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        FATAL
    };
}