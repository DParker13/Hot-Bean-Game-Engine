/**
 * @file menu.hpp
 * @author Daniel Parker (DParker13)
 * @brief Main menu window for the editor UI.
 * @version 0.1
 * @date 2025-10-17
 *
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <imgui.h>
#include <memory>
#include <vector>

#include <HotBeanEngine/editor/iwindow.hpp>

namespace HBE::Application::GUI {
    /**
     * @class Menu
     * @brief Main menu window for the editor UI.
     * 
     * Provides window visibility toggles and menu bar functionality.
     * Displays all available editor windows and allows users to show/hide them.
     */
    class Menu : public IWindow {
    private:
        std::vector<std::shared_ptr<IWindow>> &m_windows;

    public:
        Menu(std::vector<std::shared_ptr<IWindow>> &windows) : IWindow("Menu"), m_windows(windows) {}
        ~Menu() = default;

        virtual void RenderWindow() override;
    };
} // namespace HBE::Application::GUI