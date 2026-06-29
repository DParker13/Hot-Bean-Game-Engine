/**
 * @file application_state_manager.cpp
 * @author Daniel Parker (DParker13)
 * @brief Implementation of application state control.
 * @version 0.1
 * @date 2025-12-09
 *
 * @copyright Copyright (c) 2025
 */

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/application/managers/application_state_manager.hpp>

namespace HBE::Application::Managers {

    void ApplicationStateManager::QueueStateChange(ApplicationState new_state) { m_queued_state = new_state; }

    void ApplicationStateManager::ClearReloadFlag() { m_needs_scene_reload = false; }

    ApplicationState ApplicationStateManager::GetState() const { return m_state; }

    bool ApplicationStateManager::IsState(ApplicationState state) const { return m_state == state; }

    void ApplicationStateManager::UpdateGameLoopState() {
        ApplicationState previous_state = m_state;
        m_state = m_queued_state;

        // Handle transitions to Playing state
        if (m_state == ApplicationState::Playing && previous_state == ApplicationState::Stopped) {
            m_needs_scene_reload = true;
        }

        // Log state transition
        if (previous_state != m_state) {
            std::string previous_state_str = (previous_state == ApplicationState::Stopped)   ? "Stopped"
                                             : (previous_state == ApplicationState::Playing) ? "Playing"
                                                                                             : "Paused";
            std::string new_state_str = (m_state == ApplicationState::Stopped)   ? "Stopped"
                                        : (m_state == ApplicationState::Playing) ? "Playing"
                                                                                 : "Paused";

            LOG(LoggingType::INFO, "Game state transition: " + previous_state_str + " -> " + new_state_str);
        }
    }

    bool ApplicationStateManager::ShouldReloadScene() const { return m_needs_scene_reload; }

} // namespace HBE::Application::Managers
