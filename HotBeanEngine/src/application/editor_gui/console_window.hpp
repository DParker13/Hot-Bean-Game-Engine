#pragma once

#include <HotBeanEngine/application/editor_gui/window.hpp>
#include <imgui.h>

namespace HBE::Application::GUI {
    class ConsoleWindow : public IWindow {
        public:
            ConsoleWindow();
            ~ConsoleWindow() = default;

            virtual void Render() override;
    };
}