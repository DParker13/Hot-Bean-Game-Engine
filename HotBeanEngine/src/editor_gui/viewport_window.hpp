#pragma once

#include <imgui.h>

#include <HotBeanEngine/editor_gui/iwindow.hpp>

namespace HBE::Application::GUI {
    class ViewportWindow : public IWindow {
    public:
        void RenderWindow();
    };
}