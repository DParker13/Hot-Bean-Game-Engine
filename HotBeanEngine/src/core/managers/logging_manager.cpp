#include "logging_manager.hpp"

namespace Core::Managers {

    void LoggingManager::Log(LoggingType type, std::string message) {
        if (message.empty() || type < _log_level) {
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

        if (_log_path.empty()) {
            SetupDefaultLoggingPath();
        }

        // Create the missing log directories if they don't exist
        std::filesystem::create_directories(std::filesystem::path(_log_path).parent_path());

        // Open the log file in append mode and write the message
        std::ofstream log_file(_log_path, std::ios_base::app);
        if (log_file.is_open()) {
            log_file << final_message.str();
            log_file.close();
        }
    }

    void LoggingManager::SetLogPath(std::string log_path) {
        _log_path = log_path;
    }

    void LoggingManager::SetLoggingLevel(LoggingType level) {
        _log_level = level;
    }

    void LoggingManager::SetupDefaultLoggingPath() {
        if (_log_path.empty()) {
            // Determine the log directory based on the operating system and environment
            #ifdef _WIN32
                _log_path = "C:\\Windows\\Logs\\HotBeanEngine.log";
            #elif __linux__
                _log_path = "/var/log/HotBeanEngine.log";
            #elif __APPLE__
                _log_path = "/var/log/HotBeanEngine.log";
            #else
                _log_path = "logs/HotBeanEngine.log"; // default to a local logs directory
            #endif
        }
    }
}