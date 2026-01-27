/**
 * @file game_loop_manager.hpp
 * @author Daniel Parker (DParker13)
 * @brief Manages game loop state transitions and control.
 * @version 0.1
 * @date 2025-12-09
 * 
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <HotBeanEngine/application/managers/logging_manager.hpp>

namespace HBE::Application::Managers {
    /**
     * @brief Enum representing the state of the application.
     */
    enum class ApplicationState {
        Stopped,    ///< The application is stopped.
        Playing,    ///< The application is playing.
        Paused      ///< The application is paused.
    };

    /**
     * @brief Controls game loop state transitions and manages pause/resume/stop logic.
     * 
     * This class encapsulates the state machine logic for the game loop, providing
     * a clean interface for starting, pausing, stopping, and resuming the game.
     * It handles scene reloading when transitioning from Stopped to Playing state.
     */
    class GameLoopManager {
    private:
        ApplicationState m_state = ApplicationState::Stopped;
        ApplicationState m_queued_state = ApplicationState::Stopped;
        bool m_needs_scene_reload = false;
        std::shared_ptr<LoggingManager> m_logging_manager;
        
    public:
        GameLoopManager(std::shared_ptr<LoggingManager> logging_manager) : m_logging_manager(logging_manager) {}
        ~GameLoopManager() = default;
        
        /**
         * @brief Called when transitioning from one state to another.
         * Handles any necessary setup/cleanup for the state transition.
         * 
         * @param new_state The new application state
         */
        void QueueStateChange(ApplicationState new_state) { m_queued_state = new_state; }
        
        /**
         * @brief Called at the start of each frame to process state changes.
         * Should be called at the beginning of the main loop iteration.
         */
        void UpdateGameLoopState();
        
        /**
         * @brief Checks if the scene needs to be reloaded.
         * This happens when transitioning from Stopped to Playing.
         * 
         * @return true if scene reload is needed, false otherwise
         */
        bool ShouldReloadScene() const { return m_needs_scene_reload; }
        
        /**
         * @brief Clears the scene reload flag after reloading is complete.
         */
        void ClearReloadFlag() { m_needs_scene_reload = false; }
        
        /**
         * @brief Gets the previous application state.
         * @return The previous ApplicationState
         */
        ApplicationState GetState() const { return m_state; }

        /**
         * @brief Checks if the current state matches the given state.
         * @param state The ApplicationState to check against
         * @return true if the current state matches, false otherwise
         */
        bool IsState(ApplicationState state) const { return m_state == state; }
    };
}
