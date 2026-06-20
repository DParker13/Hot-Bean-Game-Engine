/**
 * @file new_project_window.cpp
 * @author Daniel Parker (DParker13)
 * @brief Implementation of the window for creating a new project.
 * @version 0.1
 * @date 2026-04-13
 *
 * @copyright Copyright (c) 2026
 */

#include "new_project_window.hpp"
#include "../editor_utils.hpp"

#include <SDL3/SDL_dialog.h>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

namespace HBE::GUI {
    void NewProjectWindow::RenderWindow() {
        if (ImGui::Begin(m_name.c_str(), &m_open)) {
            std::string directory = m_new_project.m_directory.string();
            ImGui::InputText("Project Name", &m_new_project.m_name);
            if (ImGui::InputText("Project Directory", &directory)) {
                m_new_project.m_directory = directory;
            }
            ImGui::SameLine();
            if (ImGui::Button("...")) {
                ShowFolderDialog(g_app.GetWindow(), [this](std::string_view directory) {
                    m_new_project.m_directory = std::string(directory);
                });
            }

            if (ImGui::Button("Create Project")) {
                m_project_manager->CreateNewProject(m_new_project);
                m_open = false;
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel")) {
                m_open = false;
            }
        }
        ImGui::End();
    }
} // namespace HBE::GUI