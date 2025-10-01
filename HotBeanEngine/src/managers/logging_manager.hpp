#pragma once

#include <ctime>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "../core/all_core.hpp"

using namespace HBE::Core;

// I don't like this approach, but it works for now
// TODO: Find a better way to do this. This assumes that the logging manager is a pointer and named m_logging_manager
#define LOG_CORE(type, message) \
    m_logging_manager->Log(type, message, __FILE__, __LINE__, __func__)

namespace HBE::Managers {
    class LoggingManager {
        public:
            LoggingManager(const std::string& log_path, LoggingType level, bool log_to_console);
            LoggingManager();
            ~LoggingManager();

            void Log(const LoggingType type, std::string message,
                    const char* file, int line, const char* function);
            void SetLogPath(std::string log_path);
            LoggingType GetLoggingLevel();
            void SetLoggingLevel(LoggingType level);
        
        private:
            std::ofstream m_log_file;
            std::string m_log_path;
            LoggingType m_log_level = LoggingType::ERROR;
            bool m_log_to_console = false;

            // Used for unit testing to avoid logging messages
            bool m_testing;

            void SetupDefaultLoggingPath();
            void LogToFile(const LoggingType type, std::stringstream& final_message);
    };
}