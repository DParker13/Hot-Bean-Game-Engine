#include "console_window.hpp"

namespace HBE::Application::GUI {
    ConsoleWindow::ConsoleWindow() : IWindow("Console") {}

    void ConsoleWindow::RenderWindow() {
        ImGui::Begin(m_name.c_str(), &m_open);
        ImGui::Text("This is the Console Window.");
        ImGui::End();
    }
}