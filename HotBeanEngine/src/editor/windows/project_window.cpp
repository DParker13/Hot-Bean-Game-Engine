/**
 * @file project_window.cpp
 * @author Daniel Parker (DParker13)
 * @brief Implementation of the window for managing a project's settings and properties.
 * @version 0.1
 * @date 2026-06-04
 *
 * @copyright Copyright (c) 2026
 */

#include "project_window.hpp"
#include "../editor_utils.hpp"

#include <SDL3/SDL_dialog.h>
#include <misc/cpp/imgui_stdlib.h>

namespace HBE::Application::GUI {
    void ProjectWindow::RenderWindow() {

        // Load project data when the window is first opened
        if (m_open && !m_was_opened) {
            m_was_opened = true;
            m_project = m_project_manager->m_project;
        }
        else if (!m_open) {
            m_was_opened = false;
        }

        if (ImGui::Begin(m_name.c_str(), &m_open)) {
            std::string directory = m_project.m_directory.string();
            ImGui::InputText("Project Name", &m_project.m_name);
            if (ImGui::InputText("Project Directory", &directory)) {
                m_project.m_directory = directory;
            }
            ImGui::SameLine();
            if (ImGui::Button("...")) {
                ShowFolderDialog(g_app.GetWindow(), [this](std::string_view directory) {
                    m_project.m_directory = std::string(directory);
                });
            }

            if (ImGui::Button("Save")) {
                m_project_manager->m_project = m_project;
                m_project_manager->SaveProject();
            }
            if (ImGui::Button("Close")) {
                m_open = false;
            }
        }
        ImGui::End();
    }
} // namespace HBE::Application::GUI