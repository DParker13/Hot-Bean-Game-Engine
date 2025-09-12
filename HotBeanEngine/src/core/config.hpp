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

#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>

#include "entity.hpp"
#include "component.hpp"
#include "logging_type.hpp"

using namespace HBE::Core;

namespace Config {
    // ECS (These need to be set at compile time)
    inline const Entity MAX_ENTITIES = 50000; //< Maximum number of entities that can be created
    inline const ComponentType MAX_COMPONENTS = 64; //< Maximum number of components that can be registered

    // Window
    inline std::string WINDOW_TITLE = "Hot Bean Engine";
    inline int SCREEN_WIDTH = 1280;
    inline int SCREEN_HEIGHT = 720;

    // Logging
    inline LoggingType LOGGING_LEVEL = LoggingType::DEBUG;
    inline std::string LOG_PATH = "./logs/log.txt";

    // Misc
    inline std::string ASSET_PATH = "./assets/";

    static int LoadConfig(const std::string& config_path) {
        try {
            YAML::Node config = YAML::LoadFile(config_path);

            // Window
            if (config["Window"]) {
                if (config["Window"]["title"]) {
                    WINDOW_TITLE = config["Window"]["title"].as<std::string>();
                }
                if (config["Window"]["width"]) {
                    SCREEN_WIDTH = config["Window"]["width"].as<int>();
                }
                if (config["Window"]["height"]) {
                    SCREEN_HEIGHT = config["Window"]["height"].as<int>();
                }
            }

            // Logging
            if (config["Logging"]) {
                if (config["Logging"]["level"]) {
                    LOGGING_LEVEL = static_cast<LoggingType>(config["Logging"]["level"].as<int>());
                }
                if (config["Logging"]["path"]) {
                    LOG_PATH = config["Logging"]["path"].as<std::string>();
                }
            }

            return 0;
        }
        catch (YAML::Exception& e) {
            return -1;
        }
    }
}