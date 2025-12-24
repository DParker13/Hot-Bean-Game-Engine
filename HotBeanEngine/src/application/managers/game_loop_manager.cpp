/**
 * @file game_loop_manager.cpp
 * @author Daniel Parker (DParker13)
 * @brief Implementation of game loop state control.
 * @version 0.1
 * @date 2025-12-09
 * 
 * @copyright Copyright (c) 2025
 */

#include <HotBeanEngine/application/managers/game_loop_manager.hpp>

namespace HBE::Application::Managers {
    void GameLoopManager::UpdateGameLoopState() {
        ApplicationState previous_state = m_state;
        m_state = m_queued_state;

        // Handle transitions to Playing state
        if (m_state == ApplicationState::Playing && previous_state == ApplicationState::Stopped) {
            m_needs_scene_reload = true;
        }
        
        // Log state transition
        if (previous_state != m_state) {
            std::string previous_state_str = (previous_state == ApplicationState::Stopped) ? "Stopped" :
                                        (previous_state == ApplicationState::Playing) ? "Playing" : "Paused";
            std::string new_state_str = (m_state == ApplicationState::Stopped) ? "Stopped" :
                                        (m_state == ApplicationState::Playing) ? "Playing" : "Paused";
            
            LOG_CORE(LoggingType::INFO, "Game state transition: " + previous_state_str + " -> " + new_state_str);
        }
    }
}
