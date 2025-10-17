#pragma once

#include <imgui.h>

#include <HotBeanEngine/application/editor_gui/window.hpp>
#include <HotBeanEngine/application/application.hpp>

namespace HBE::Application::GUI {
    class ComponentsWindow : public IWindow {
        public:
            ComponentsWindow();
            ~ComponentsWindow() = default;

            virtual void Render() override;
    };
}