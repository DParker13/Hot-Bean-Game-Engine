/**
 * @file iwindow.hpp
 * @author Daniel Parker (DParker13)
 * @brief Interface for GUI windows using ImGui.
 * @version 0.1
 * @date 2025-10-26
 * 
 * @copyright Copyright (c) 2025
 */

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

        virtual void RenderWindow() = 0;
    };
}