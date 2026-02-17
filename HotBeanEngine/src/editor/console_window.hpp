/**
 * @file console_window.hpp
 * @author Daniel Parker (DParker13)
 * @brief Debug console window for the editor UI.
 * @version 0.1
 * @date 2025-10-17
 *
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <HotBeanEngine/editor/iwindow.hpp>
#include <imgui.h>

namespace HBE::Application::GUI {
    /**
     * @class ConsoleWindow
     * @brief Debug console window for the editor UI.
     *
     * Displays debug output and application messages.
     * Provides a centralized location for viewing log messages and diagnostics.
     */
    class ConsoleWindow : public IWindow {
    public:
        ConsoleWindow();
        ~ConsoleWindow() = default;

        virtual void RenderWindow() override;
    };
} // namespace HBE::Application::GUI