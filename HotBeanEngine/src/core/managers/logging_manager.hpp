#pragma once

#include <ctime>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "../ecs/all_ecs.hpp"

using namespace Core::ECS;

#define LOG_CORE(type, message) \
    m_logging_manager->Log(type, message, __FILE__, __LINE__, __func__)

namespace Core::Managers {
    class LoggingManager {
        public:
            LoggingManager(const std::string& log_path, LoggingType level);
            LoggingManager();
            ~LoggingManager();

            void Log(const LoggingType type, std::string message,
                    const char* file, int line, const char* function);
            void SetLogPath(std::string log_path);
            void SetLoggingLevel(LoggingType level);
        
        private:
            std::ofstream m_log_file;
            std::string m_log_path;
            LoggingType m_log_level;

            // Used for unit testing to avoid logging messages
            bool m_testing;

            void SetupDefaultLoggingPath();
            void LogToFile(const LoggingType type, std::stringstream& final_message);
    };
}