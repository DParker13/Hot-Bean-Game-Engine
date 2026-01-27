#pragma once

#include <imgui.h>
#include <vector>
#include <memory>

#include <HotBeanEngine/editor/iwindow.hpp>

namespace HBE::Application::GUI {
    class Menu : public IWindow {
        private:
            std::vector<std::shared_ptr<IWindow>>& m_windows;
            
        public:
            Menu(std::vector<std::shared_ptr<IWindow>>& windows) : IWindow("Menu"), m_windows(windows) {}
            ~Menu() = default;

            virtual void RenderWindow() override;
    };
}