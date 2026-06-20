/**
 * @file new_project_window.hpp
 * @author Daniel Parker (DParker13)
 * @brief Window for creating a new project.
 * @version 0.1
 * @date 2026-04-13
 *
 * @copyright Copyright (c) 2026
 */
#pragma once

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/editor/iwindow.hpp>

#include "../project_manager.hpp"

namespace HBE::GUI {
    using namespace Core;

    /**
     * @class ConfigWindow
     * @brief Window for managing configuration settings.
     *
     * Provides a user interface for specifying configuration details and managing existing settings.
     */
    class ConfigWindow : public IWindow {
    private:
        bool m_was_opened = false;
        bool m_log_to_console = true;
        std::filesystem::path m_startup_project;
        LoggingType m_log_level = LoggingType::DEBUG;
        std::filesystem::path m_logging_directory;

    public:
        ConfigWindow() : IWindow("Config Settings", false, true) {}
        ~ConfigWindow() = default;

        void RenderWindow() override;

    private:
        void LoadConfigFromEnv();
        void SaveConfigToFile();
    };
} // namespace HBE::GUI