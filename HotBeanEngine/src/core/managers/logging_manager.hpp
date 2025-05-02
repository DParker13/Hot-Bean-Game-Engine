#pragma once

#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <filesystem>

#include "../ecs/all_ecs.hpp"

using namespace Core::ECS;

namespace Core::Managers {
    class LoggingManager {
        public:
            LoggingManager() = default;

            void Log(LoggingType type, std::string message);
            void SetLogPath(std::string log_path);
            void SetLoggingLevel(LoggingType level);
        
        private:
            std::string _log_path;
            LoggingType _log_level;

            void SetupDefaultLoggingPath();
    };
}