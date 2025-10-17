#include "menu.hpp"

namespace HBE::Application::GUI {
    void Menu::Render() {
        if (ImGui::BeginMainMenuBar()) {
            // if (ImGui::BeginMenu("File")) {
            //     if (ImGui::MenuItem("Exit")) {
            //         //Application::Get().RequestClose();
            //     }
            //     ImGui::EndMenu();
            // }
            if (ImGui::BeginMenu("Windows")) {
                for (auto& window : m_windows) {
                    if (window->m_name.c_str() == "Menu") {
                        continue;
                    }

                    ImGui::Checkbox(window->m_name.c_str(), &window->m_open);
                    ImGui::SameLine();
                    if (ImGui::MenuItem(window->m_name.c_str())) {
                        window->m_open = !window->m_open;
                    }
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }
}