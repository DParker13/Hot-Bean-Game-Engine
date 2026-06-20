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

namespace HBE::GUI {
    class IWindow {
    public:
        bool m_open;
        bool m_menu_item_visible;
        std::string m_name;

    public:
        IWindow(std::string name, bool open, bool menu_item_visible)
            : m_name(name), m_open(open), m_menu_item_visible(menu_item_visible) {}
        IWindow(std::string name, bool open) : IWindow(name, open, true) {}
        IWindow(std::string name) : IWindow(name, true, true) {}
        IWindow() : IWindow("Default Window", true, true) {}
        virtual ~IWindow() = default;

        virtual void RenderWindow() = 0;
    };
} // namespace HBE::GUI