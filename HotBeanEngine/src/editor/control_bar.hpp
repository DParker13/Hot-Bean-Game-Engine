/**
 * @file control_bar.hpp
 * @author Daniel Parker (DParker13)
 * @brief Control bar window for game state management.
 * @version 0.1
 * @date 2025-10-30
 *
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <HotBeanEngine/application/application.hpp>
#include <imgui.h>

namespace HBE::Application::GUI {
    /**
     * @class ControlBar
     * @brief Control bar window for game state management.
     *
     * Provides buttons for starting, pausing, and stopping game simulation.
     * Integrates with the Application to control game loop state.
     */
    class ControlBar {
    public:
        ControlBar() = default;
        ~ControlBar() = default;

        void Render();
    };
} // namespace HBE::Application::GUI