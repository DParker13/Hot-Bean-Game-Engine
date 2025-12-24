#include "control_bar.hpp"

namespace HBE::Application::GUI {
    void ControlBar::RenderWindow() {
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::Button("Start")) {
                // Start the game
                g_app.PlayGame();
            }

            if (ImGui::Button("Pause")) {
                // Pause the game
                g_app.PauseGame();
            }

            if (ImGui::Button("Stop")) {
                // Stop the game
                g_app.StopGame();
            }

            ImGui::EndMainMenuBar();
        }
    }
}