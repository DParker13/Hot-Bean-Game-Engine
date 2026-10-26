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
#include <string>

#include <HotBeanEngine/core/component.hpp>
#include <HotBeanEngine/core/entity.hpp>
#include <HotBeanEngine/core/iserializable.hpp>
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

    class Config : public ISerializable {
    private:
        std::filesystem::path m_log_directory = "./logs";
        LoggingType m_logging_level = LoggingType::DEBUG;
        bool m_log_to_console = true;
        std::filesystem::path m_startup_project_path = "";

    public:
        Config() = default;

        std::filesystem::path GetLogDirectory() const { return m_log_directory; }
        LoggingType GetLoggingLevel() const { return m_logging_level; }
        bool GetLogToConsole() const { return m_log_to_console; }
        std::filesystem::path GetStartupProjectPath() const { return m_startup_project_path; }

        void SetLogDirectory(std::filesystem::path dir) { m_log_directory = std::move(dir); }
        void SetLoggingLevel(LoggingType level) { m_logging_level = level; }
        void SetLogToConsole(bool log_to_console) { m_log_to_console = log_to_console; }
        void SetStartupProjectPath(std::filesystem::path path) { m_startup_project_path = std::move(path); }

        void Serialize(ISerializationWriter &out) const override {
            out.BeginSection("Project");
            out.Write("startup_path", m_startup_project_path);
            out.WriteComment("Path to the project that should be loaded on startup");
            out.EndSection();

            out.BeginSection("Logging");
            out.Write("directory", m_log_directory);
            out.WriteComment("Directory where log files will be stored");
            out.WriteEnum("level", m_logging_level);
            out.WriteComment("DEBUG = 0, INFO, WARNING, ERROR, FATAL = 4");
            out.Write("console", m_log_to_console);
            out.WriteComment("Whether to also log messages to the console (true/false)");
            out.EndSection();
        }

        void Deserialize(ISerializationReader &in) override {
            in.BeginSection("Project");
            in.Read("startup_path", m_startup_project_path);
            in.EndSection();

            in.BeginSection("Logging");
            in.Read("directory", m_log_directory);
            in.ReadEnum("level", m_logging_level);
            in.Read("console", m_log_to_console);
            in.EndSection();
        }
    };

    /// @brief Global config instance. Access via g_config macro.
    inline Config g_config{};
} // namespace HBE::Core