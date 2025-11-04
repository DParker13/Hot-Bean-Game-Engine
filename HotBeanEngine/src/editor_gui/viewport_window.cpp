#include "viewport_window.hpp"

namespace HBE::Application::GUI {
    void ViewportWindow::RenderWindow() {
        ImGui::Begin("Viewport");

        // Viewport rendering logic goes here

        ImGui::End();
    }
}