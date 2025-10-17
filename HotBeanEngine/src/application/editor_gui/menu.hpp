#pragma once

#include <imgui.h>

#include "components_window.hpp"
#include "console_window.hpp"
#include "viewport_window.hpp"

namespace HBE::Application::GUI {
    class Menu : public IWindow {
        private:
            std::vector<std::shared_ptr<IWindow>>& m_windows;
            
        public:
            Menu(std::vector<std::shared_ptr<IWindow>>& windows) : IWindow("Menu"), m_windows(windows) {}
            ~Menu() = default;

            virtual void Render() override;
    };
}