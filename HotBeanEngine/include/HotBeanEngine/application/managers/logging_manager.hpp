/**
 * @file logging_manager.hpp
 * @author Daniel Parker (DParker13)
 * @brief Manages application-wide logging functionality.
 * @version 0.1
 * @date 2025-04-16
 *
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <sstream>

#include <HotBeanEngine/core/all_core.hpp>

namespace HBE::Application::Managers {
    using namespace HBE::Core;

// I don't like this approach, but it works for now
// TODO: Find a better way to do this. This assumes that the logging manager is a pointer and named m_logging_manager
#define LOG_CORE(type, message) m_logging_manager->Log(type, message, __FILE__, __LINE__, __func__)

    /**
     * @brief Handles application-wide logging functionality.
     * Manages log levels, file output, and message formatting.
     * Supports console and file logging with severity levels.
     */
    class LoggingManager {
    private:
        std::ofstream m_log_file;
        std::string m_log_path;
        LoggingType m_log_level = LoggingType::ERROR;
        bool m_log_to_console = false;

        // Used for unit testing to avoid logging messages
        bool m_testing;

    public:
        LoggingManager(const std::string &log_path, LoggingType level, bool log_to_console);
        LoggingManager();
        ~LoggingManager();

        void Log(const LoggingType type, std::string_view message, const char *file, int line, const char *function);
        void SetLogPath(std::string_view log_path);
        LoggingType GetLoggingLevel();
        void SetLoggingLevel(LoggingType level);

    private:
        void SetupDefaultLoggingPath();
        void LogToFile(const LoggingType type, std::stringstream &final_message);
    };
} // namespace HBE::Application::Managers