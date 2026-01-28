/**
 * @file console_window.cpp
 * @author Daniel Parker (DParker13)
 * @brief Implementation of the console window for the editor GUI.
 * Displays debug output and application messages.
 * @version 0.1
 * @date 2025-10-17
 *
 * @copyright Copyright (c) 2025
 */

#include "console_window.hpp"

namespace HBE::Application::GUI {
    ConsoleWindow::ConsoleWindow() : IWindow("Console") {}

    void ConsoleWindow::RenderWindow() {
        ImGui::Begin(m_name.c_str(), &m_open);
        ImGui::Text("This is the Console Window.");
        ImGui::End();
    }
} // namespace HBE::Application::GUI