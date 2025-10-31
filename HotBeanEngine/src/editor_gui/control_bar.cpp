#include "control_bar.hpp"

namespace HBE::Application::GUI {
    void ControlBar::RenderWindow() {
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::Button("Start")) {
                // Start the game
                g_app.GetState() = ApplicationState::Playing;
            }

            if (ImGui::Button("Pause")) {
                // Pause the game
                g_app.GetState() = ApplicationState::Paused;
            }

            if (ImGui::Button("Stop")) {
                // Stop the game
                g_app.GetState() = ApplicationState::Stopped;
            }

            ImGui::EndMainMenuBar();
        }
    }
}