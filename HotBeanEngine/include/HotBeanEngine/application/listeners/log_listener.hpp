/**
 * @file log_listener.hpp
 * @author Daniel Parker (DParker13)
 * @brief Interface for objects that need to track log messages.
 * @version 0.1
 * @date 2026-02-23
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

#include <HotBeanEngine/core/logging_type.hpp>
#include <string>

namespace HBE::Application::Listeners {
    /**
     * @brief Base class for listening to log messages.
     *
     * Implement this base class to receive notifications when log messages are generated.
     * Register with LoggingManager via RegisterLogListener.
     */
    class ILogListener {
    public:
        ~ILogListener() = default;

        /**
         * @brief Called when a log message is generated.
         * @param message The log message.
         */
        virtual void OnLog(Core::LoggingType level, std::string_view message) = 0;
    };
} // namespace HBE::Application
