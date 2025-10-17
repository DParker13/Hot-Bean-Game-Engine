#pragma once

#include <string>

namespace HBE::Application::GUI {
    class IWindow {
        public:
            bool m_open = true;
            std::string m_name = "Default Window";

        public:
            IWindow(std::string name) : m_name(name) {}
            IWindow() : m_name("Default Window") {}
            virtual ~IWindow() = default;

            virtual void Render() = 0;
    };
}