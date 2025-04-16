/**
 * @file config.h
 * @author Daniel Parker (DParker13)
 * @brief Setups up global constants (This should be moved to a config file in the future)
 * @version 0.1
 * @date 2025-03-02
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once

#include <string>

#include "logging_type.hpp"

using namespace Core::ECS;

namespace Config {
    // Window
    inline const char* WINDOW_TITLE = "Hot Bean Engine";
    inline const int SCREEN_WIDTH = 1280;
    inline const int SCREEN_HEIGHT = 720;

    // Logging
    inline const LoggingType LOGGING_LEVEL = LoggingType::DEBUG;
    inline const std::string LOG_PATH = "./logs/log.txt";

    // ECS
    
}