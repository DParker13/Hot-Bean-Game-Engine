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

#include <HotBeanEngine/application/listeners/log_listener.hpp>
#include <HotBeanEngine/editor/iwindow.hpp>
#include <deque>
#include <imgui.h>

namespace HBE::Application::GUI {
    /**
     * @class ConsoleWindow
     * @brief Debug console window for the editor UI.
     *
     * Displays debug output and application messages.
     * Provides a centralized location for viewing log messages and diagnostics.
     */
    class ConsoleWindow : public IWindow, public Listeners::ILogListener {
    private:
        // Buffer to store log messages with their logging type
        std::deque<std::pair<HBE::Core::LoggingType, std::string>> m_logBuffer;
        // Maximum number of log messages to keep in the buffer
        size_t m_maxLogBufferSize = 10000;
        // Flag to scroll to bottom when new log is added
        bool m_shouldScrollToBottom = false;
        // Flag to enable/disable auto-scroll feature
        bool m_autoScroll = true;
        // Minimum logging level to display
        HBE::Core::LoggingType m_loggingLevelFilter = HBE::Core::LoggingType::DEBUG;

    public:
        ConsoleWindow();
        ~ConsoleWindow() = default;

        virtual void RenderWindow() override;
        virtual void OnLog(HBE::Core::LoggingType level, std::string_view message) override;
    };
} // namespace HBE::Application::GUI