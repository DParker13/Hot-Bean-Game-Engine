/**
 * @file menu.cpp
 * @author Daniel Parker (DParker13)
 * @brief Implementation of the main menu window for the editor GUI.
 * Provides window visibility toggles and menu bar functionality.
 * @version 0.1
 * @date 2025-10-17
 *
 * @copyright Copyright (c) 2025
 */

#include "menu.hpp"

namespace HBE::Application::GUI {
    void Menu::RenderWindow() {
        if (ImGui::BeginMainMenuBar()) {
            // if (ImGui::BeginMenu("File")) {
            //     if (ImGui::MenuItem("Exit")) {
            //         //Application::Get().RequestClose();
            //     }
            //     ImGui::EndMenu();
            // }
            if (ImGui::BeginMenu("Windows")) {
                for (auto &window : m_windows) {
                    if (window->m_name.c_str() == "Menu") {
                        continue;
                    }

                    if (ImGui::Checkbox(window->m_name.c_str(), &window->m_open)) {
                        window->m_open = !window->m_open;
                    }
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }
} // namespace HBE::Application::GUI