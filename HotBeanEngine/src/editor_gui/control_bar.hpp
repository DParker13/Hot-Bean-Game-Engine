#pragma once

#include <imgui.h>
#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/editor_gui/iwindow.hpp>

namespace HBE::Application::GUI {
    class ControlBar : public IWindow {
        public:
            ControlBar() : IWindow("Control Bar") {}
            ~ControlBar() = default;

            virtual void RenderWindow() override;
    };
}