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

namespace HBE::GUI {
    using Application::Managers::ApplicationState::Paused;
    using Application::Managers::ApplicationState::Playing;
    using Application::Managers::ApplicationState::Stopped;

    void ControlBar::Render() {
        if (ImGui::BeginMainMenuBar()) {
            ImGui::BeginDisabled(!g_app.GetSceneManager().GetCurrentScene());
            if (ImGui::Button("Start")) {
                // Start the game
                g_app.GetAppStateManager().QueueStateChange(Playing);
            }

            if (ImGui::Button("Pause")) {
                // Pause the game
                g_app.GetAppStateManager().QueueStateChange(Paused);
            }

            if (ImGui::Button("Stop")) {
                // Stop the game
                g_app.GetAppStateManager().QueueStateChange(Stopped);
            }
            ImGui::EndDisabled();

            ImGui::EndMainMenuBar();
        }
    }
} // namespace HBE::GUI