#pragma once

#include <HotBeanEngine/editor_gui/iwindow.hpp>
#include <imgui.h>

namespace HBE::Application::GUI {
    class ConsoleWindow : public IWindow {
        public:
            ConsoleWindow();
            ~ConsoleWindow() = default;

            virtual void RenderWindow() override;
    };
}