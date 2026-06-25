/**
 * @file config.h
 * @author Daniel Parker (DParker13)
 * @brief Setups up global constants.
 * @version 0.1
 * @date 2025-03-02
 *
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>

#include <HotBeanEngine/core/component.hpp>
#include <HotBeanEngine/core/entity.hpp>
#include <HotBeanEngine/core/logging_type.hpp>

namespace HBE::Core {
    // ECS (These need to be set at compile time)
    inline const EntityID MAX_ENTITIES = 50000;   // Maximum number of entities that can be created
    inline const ComponentID MAX_COMPONENTS = 64; // Maximum number of components that can be registered
    inline const float VERSION = 0.1f;            // Engine version

    // Config
    inline const std::filesystem::path CONFIG_DIRECTORY = "./"; // Path to the config file
    inline const std::string CONFIG_NAME = "config.yaml";       // Config file name

    // Logging
    inline const std::string LOG_FILE_NAME = "HotBeanEngine.log"; // Log file name
    inline std::filesystem::path LOG_DIRECTORY = "./logs";        // Directory where log files will be stored
    inline LoggingType LOGGING_LEVEL = LoggingType::DEBUG; // Minimum logging level (DEBUG, INFO, WARNING, ERROR, FATAL)
    inline bool LOG_TO_CONSOLE = true;                     // Whether to also log messages to the console (true/false)

    // Project
    // Startup project path (can be set in config.yaml)
    // This stores the last project that was opened or created, and will be loaded on startup.
    inline std::filesystem::path STARTUP_PROJECT_PATH = "";

    /**
     * @brief Saves the current configuration to a YAML file. This includes logging settings and the startup project
     * path.
     * @return Returns 0 on success, -1 on failure.
     */
    inline int SaveConfig() {
        YAML::Emitter out;
        out.SetIndent(2);

        out << YAML::BeginMap;

        // Project
        out << YAML::Key << "Project" << YAML::Value;
        out << YAML::BeginMap;
        out << YAML::Key << "startup_path" << YAML::Value << YAML::DoubleQuoted << STARTUP_PROJECT_PATH.string()
            << YAML::Auto << YAML::Comment("Path to the project that should be loaded on startup");

        // Logging
        out << YAML::Key << "Logging" << YAML::Value;
        out << YAML::BeginMap;
        out << YAML::Key << "directory" << YAML::Value << YAML::DoubleQuoted << LOG_DIRECTORY.string() << YAML::Auto
            << YAML::Comment("Directory where log files will be stored");
        out << YAML::Key << "level" << YAML::Value << static_cast<int>(LOGGING_LEVEL)
            << YAML::Comment("DEBUG = 0, INFO, WARNING, ERROR, FATAL = 4");
        out << YAML::Key << "console" << YAML::Value << YAML::TrueFalseBool << LOG_TO_CONSOLE << YAML::Auto;
        out << YAML::EndMap;

        out << YAML::EndMap;

        // Ensure directory exists
        if (!CONFIG_DIRECTORY.empty()) {
            std::filesystem::create_directories(CONFIG_DIRECTORY);
        }

        std::ofstream fout(CONFIG_DIRECTORY / CONFIG_NAME);
        if (fout.is_open()) {
            fout << out.c_str();
            fout.close();
            return 0;
        }
        else {
            std::cerr << "Failed to open config file for writing: " << (CONFIG_DIRECTORY / CONFIG_NAME).string()
                      << "\n";
            return -1;
        }
    }

    /**
     * @brief Loads the configuration from a YAML file. If the file does not exist or is invalid, it will create a new
     * config file with default values.
     * @return Returns 0 on success, -1 on failure.
     */
    inline int LoadConfig() {
        try {
            YAML::Node config = YAML::LoadFile((CONFIG_DIRECTORY / CONFIG_NAME).string());

            // Logging
            if (config["Logging"]["level"]) {
                LOGGING_LEVEL = static_cast<LoggingType>(config["Logging"]["level"].as<int>());
            }
            if (config["Logging"]["directory"]) {
                LOG_DIRECTORY = config["Logging"]["directory"].as<std::string>();
            }
            if (config["Logging"]["console"]) {
                LOG_TO_CONSOLE = config["Logging"]["console"].as<bool>();
            }

            // Project
            if (config["Project"]["startup_path"]) {
                STARTUP_PROJECT_PATH = config["Project"]["startup_path"].as<std::string>();
            }

            return 0;
        } catch (YAML::Exception &) {
            return SaveConfig();
        }
    }
} // namespace HBE::Core