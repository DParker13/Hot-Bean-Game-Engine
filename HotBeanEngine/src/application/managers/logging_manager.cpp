/**
 * @file logging_manager.cpp
 * @author Daniel Parker (DParker13)
 * @brief Implementation of the logging manager that handles application logging.
 * Provides debug, info, warning, and error level logging with file and console output.
 * @version 0.1
 * @date 2025-04-16
 *
 * @copyright Copyright (c) 2025
 */

#include <HotBeanEngine/application/managers/logging_manager.hpp>

namespace HBE::Application::Managers {

    LoggingManager::LoggingManager(const std::string &log_path, LoggingType level, bool log_to_console)
        : m_log_path(log_path), m_log_level(level), m_log_to_console(log_to_console), m_testing(false) {
        SetupDefaultLoggingPath();

        // Create the missing log directories if they don't exist
        std::filesystem::create_directories(std::filesystem::path(m_log_path).parent_path());
    }

    LoggingManager::LoggingManager() : m_testing(true) { SetupDefaultLoggingPath(); }

    LoggingManager::~LoggingManager() {
        if (m_log_file.is_open()) {
            m_log_file.close();
        }
    }

    void LoggingManager::Log(const LoggingType type, std::string_view message, const char *file, int line,
                             const char *function) {
        if (m_testing || message.empty() || type < m_log_level) {
            return;
        }

        std::stringstream final_message;
        std::time_t t = std::time(nullptr);
        std::tm *now = std::localtime(&t);

        if (!now) {
            std::cerr << "LoggingManager: localtime() failed" << std::endl;
            return;
        }

        std::ostream *out_stream = &std::clog;
        std::string_view level_tag;

        switch (type) {
        case LoggingType::DEBUG:
            level_tag = "[DEBUG] ";
            break;
        case LoggingType::INFO:
            level_tag = "[INFO] ";
            break;
        case LoggingType::WARNING:
            level_tag = "[WARNING] ";
            break;
        case LoggingType::ERROR:
            level_tag = "[ERROR] ";
            out_stream = &std::cerr;
            break;
        case LoggingType::FATAL:
            level_tag = "[FATAL] ";
            out_stream = &std::cerr;
            break;
        }

        // Add timestamp
        final_message << std::put_time(now, "%Y-%m-%d %H:%M:%S") << ": ";

        // Add log level
        final_message << level_tag;

        // Add file, line number, and function (if ERROR or FATAL)
        if (file && line >= 0 && function && type >= LoggingType::ERROR) {
            std::string filename = std::filesystem::path(file).filename().string();
            final_message << " [" << filename << ":" << line << " " << function << "()]";
        }

        // Add message
        final_message << " " << message;

        // Output to console
        if (m_log_to_console) {
            *out_stream << final_message.str() << std::endl;
        }

        LogToFile(type, final_message);
    }

    void LoggingManager::LogToFile(const LoggingType type, std::stringstream &final_message) {
        if (!m_log_file.is_open()) {
            // Try to open the log file in append mode
            m_log_file.open(m_log_path, std::ios_base::app);

            // Double check the file is open, otherwise throw an error
            if (!m_log_file.is_open()) {
                std::cerr << "Failed to open/create log file " << m_log_path << std::endl;
                throw std::runtime_error("Failed to open/create log file");
            }
        }

        m_log_file << final_message.str() << std::endl;

        // Close and save the log file if the type is FATAL
        if (type == LoggingType::FATAL) {
            m_log_file.close();
        }
    }

    void LoggingManager::SetLogPath(std::string_view log_path) { m_log_path = log_path; }

    LoggingType LoggingManager::GetLoggingLevel() { return m_log_level; }

    void LoggingManager::SetLoggingLevel(LoggingType level) { m_log_level = level; }

    void LoggingManager::SetupDefaultLoggingPath() {
        if (m_log_path.empty()) {
// Determine the log directory based on the operating system and environment
#ifdef _WIN32
            m_log_path = "C:\\Windows\\Logs\\HotBeanEngine\\default.log";
#elif __linux__
            m_log_path = "/var/log/HotBeanEngine.log";
#elif __APPLE__
            m_log_path = "/var/log/HotBeanEngine.log";
#else
            m_log_path = "logs/HotBeanEngine.log"; // default to a local logs directory
#endif
        }
    }
} // namespace HBE::Application::Managers