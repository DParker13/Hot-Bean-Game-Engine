#include "logging_manager.hpp"

namespace Core::Managers {

    LoggingManager::LoggingManager(const std::string& log_path, LoggingType level)
        : m_log_path(log_path), m_log_level(level) {
        SetupDefaultLoggingPath();

        // Create the missing log directories if they don't exist
        std::filesystem::create_directories(std::filesystem::path(m_log_path).parent_path());
    }

    LoggingManager::LoggingManager() {
        SetupDefaultLoggingPath();
    }

    LoggingManager::~LoggingManager() {
        if (m_log_file.is_open()) {
            m_log_file.close();
        }
    }

    void LoggingManager::Log(LoggingType type, std::string message) {
        if (m_testing ||message.empty() || type < m_log_level) {
            return;
        }

        std::stringstream final_message;
        std::time_t t = std::time(nullptr);
        std::tm* now = std::localtime(&t);

        final_message << std::put_time(now, "%Y-%m-%d %H:%M:%S") << ": ";

        switch (type) {
            case LoggingType::DEBUG:
                final_message << "[DEBUG] " << message << std::endl;
                std::clog << final_message.str() << std::endl;
                break;
            case LoggingType::INFO:
                final_message << "[INFO] " << message << std::endl;
                std::clog << final_message.str() << std::endl;
                break;
            case LoggingType::WARNING:
                final_message << "[WARNING] " << message << std::endl;
                std::clog << final_message.str() << std::endl;
                break;
            case LoggingType::ERROR:
                final_message << "[ERROR] " << message << std::endl;
                std::cerr << final_message.str() << std::endl;
                break;
            case LoggingType::FATAL:
                final_message << "[FATAL] " << message << std::endl;
                std::cerr << final_message.str() << std::endl;
                break;
        }
        
        if (m_log_file.is_open()) {
            m_log_file << final_message.str();
        }
        else {
            // Open the log file in append mode and write the message
            m_log_file.open(m_log_path, std::ios_base::app);
            if (m_log_file.is_open()) {
                m_log_file << final_message.str();
            }
            else {
                std::cerr << "Failed to open/create default log file " << m_log_path << std::endl;
            }
        }
    }

    void LoggingManager::SetLogPath(std::string log_path) {
        m_log_path = log_path;
    }

    void LoggingManager::SetLoggingLevel(LoggingType level) {
        m_log_level = level;
    }

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
}