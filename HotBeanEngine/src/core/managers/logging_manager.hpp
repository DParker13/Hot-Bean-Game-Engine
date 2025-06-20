#pragma once

#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>

#include "../ecs/all_ecs.hpp"

using namespace Core::ECS;

namespace Core::Managers {
    class LoggingManager {
        public:
            LoggingManager(const std::string& log_path, LoggingType level);
            LoggingManager();
            ~LoggingManager();

            void Log(LoggingType type, std::string message);
            void SetLogPath(std::string log_path);
            void SetLoggingLevel(LoggingType level);
        
        private:
            std::ofstream m_log_file;
            std::string m_log_path;
            LoggingType m_log_level;

            // Used for unit testing to avoid logging messages
            bool m_testing;

            void SetupDefaultLoggingPath();
    };
}