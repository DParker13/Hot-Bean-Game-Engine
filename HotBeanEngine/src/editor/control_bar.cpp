/**
 * @file control_bar.cpp
 * @author Daniel Parker (DParker13)
 * @brief Implementation of the control bar window for game state management.
 * Provides buttons for starting, pausing, and stopping the game simulation.
 * @version 0.1
 * @date 2025-10-30
 *
 * @copyright Copyright (c) 2025
 */

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
} // namespace HBE::Application::GUI