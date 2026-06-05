/**
 * @file config_window.cpp
 * @author Daniel Parker (DParker13)
 * @brief Implementation of the window for managing configuration settings.
 * @version 0.1
 * @date 2026-06-04
 *
 * @copyright Copyright (c) 2026
 */

#include "config_window.hpp"
#include "../editor_utils.hpp"

#include <SDL3/SDL_dialog.h>
#include <misc/cpp/imgui_stdlib.h>

namespace HBE::Application::GUI {
    namespace {
        constexpr SDL_DialogFileFilter kProjectFileFilters[] = {
            {"Project Files", "yaml;yml"},
            {"All Files", "*"},
        };
    } // namespace

    void ConfigWindow::RenderWindow() {

        // Load configuration data when the window is first opened
        if (m_open && !m_was_opened) {
            m_was_opened = true;
            LoadConfigFromEnv();
        }
        else if (!m_open) {
            m_was_opened = false;
        }

        if (ImGui::Begin(m_name.c_str(), &m_open)) {
            std::string startup_project = m_startup_project.string();
            if (ImGui::InputText("Startup Project", &startup_project)) {
                m_startup_project = startup_project;
            }
            ImGui::SameLine();
            if (ImGui::Button("...##startup_project_picker")) {
                ShowFileDialog(g_app.GetWindow(), kProjectFileFilters, static_cast<int>(std::size(kProjectFileFilters)),
                               [this](std::string_view path) { m_startup_project = std::string(path); });
            }

            std::string logging_directory = m_logging_directory.string();
            if (ImGui::InputText("Log Directory", &logging_directory)) {
                m_logging_directory = logging_directory;
            }
            ImGui::SameLine();
            if (ImGui::Button("...##log_directory_picker")) {
                ShowFolderDialog(g_app.GetWindow(),
                                 [this](std::string_view directory) { m_logging_directory = std::string(directory); });
            }

            int log_level_int = static_cast<int>(m_log_level);
            if (ImGui::Combo("Log Level", &log_level_int, "DEBUG\0INFO\0WARNING\0ERROR\0FATAL\0")) {
                m_log_level = static_cast<LoggingType>(log_level_int);
            }

            if (ImGui::Checkbox("Log to Console", &m_log_to_console)) {
                // Log to console changed
            }

            if (ImGui::Button("Save")) {
                SaveConfigToFile();
                m_open = false;
            }
            if (ImGui::Button("Close")) {
                m_open = false;
            }
        }
        ImGui::End();
    }

    void ConfigWindow::LoadConfigFromEnv() {
        LoadConfig();

        // Project
        m_startup_project = STARTUP_PROJECT_PATH;

        // Logging
        m_log_level = LOGGING_LEVEL;
        m_logging_directory = LOG_DIRECTORY;
        m_log_to_console = LOG_TO_CONSOLE;
    }

    void ConfigWindow::SaveConfigToFile() {
        // Project
        STARTUP_PROJECT_PATH = m_startup_project;

        // Logging
        g_app.SetLogDirectory(m_logging_directory);
        g_app.SetLoggingLevel(m_log_level);
        LOG_TO_CONSOLE = m_log_to_console;

        SaveConfig();
    }
} // namespace HBE::Application::GUI